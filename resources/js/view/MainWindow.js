
var PageRouter = function(master){
    this.redirect = function(name, args){
        master.openPage(name, args);
    }
    return this;
}

var MainWindowView = Backbone.View.extend({
    el: "body",
    noThrow:true,
    initialize:function(options){
        _(this).bindAll("openPage","show","loaded", "notifyError", "checkVersion");
        this.models = {};
        this.bindModels(options);
        this.active = null;
    },

    openPage: function(name, args){
        if(!name || name instanceof Object){
            args = name;
            name = "default";
        }
        if(name=="default" && !this.models.accounts.length)
        {
            name = "generate";
            args = {message:"generating your very first address"};
        }
        var view =  this.subpages[name];
        if(view!=undefined){
            if(this.active && this.active!=view) this.active.hide();
            this.active = view;
            this.menu.setCursor(this.menuAlias[name]||name);
            view.show(args);
        }
    },

    bindModels:function(object){
        for(var i in object){
            if(/templates|noThrow/.test(i)){
                this[i] = object[i];
            }
            else this.models[i] = object[i];
        }
    },

    _render:function(){
        this.$el.prepend(this.templates.get("main_page")({info:this.models.info}));

        this.models.events.onError(this.notifyError);

        this.router = new PageRouter(this);
        this.subpages = {};
        this.subpages.send = new SendPageView
        ({
            accounts: this.models.accounts, 
            addressbook:this.models.addressbook, 
            el:this.$el.find("#page_send"), 
            router:this.router, 
            clipboard: this.models.clipboard,
            addressValidator: this.models.addressValidator,
            fee: this.models.fee,
            resolver: this.models.resolver,
            templates:this.templates
        });
        this.subpages.receive = new ReceivePageView
        ({
            accounts:this.models.accounts, 
            clipboard: this.models.clipboard, 
            el:this.$el.find("#page_receive"), 
            templates:this.templates,
            router:this.router
        });
        this.subpages.addressbook = new AddressBookPageView
        ({
            addressbook:this.models.addressbook,
            el:this.$el.find("#page_addressbook"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.transactions = new TransactionsPageView
        ({
            accounts:this.models.accounts,
            clipboard: this.models.clipboard,
            router: this.router,
            addressbook: this.models.addressbook,
            transactions:this.models.transactions,
            el:this.$el.find("#page_transactions"),
            templates:this.templates
        });
        this.subpages.password = new ChangePasswordPageView
        ({
            accounts:this.models.accounts,
            el:this.$el.find("#page_editAddress"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.generate = new GeneratePageView
        ({
            accounts:this.models.accounts,
            el:this.$el.find("#page_newAddress"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.import = new ImportKeyPageView
        ({
            filesystem:this.models.filesystem,
            wallet:this.models.accounts,
            el:this.$el.find("#page_importAddress"),
            router:this.router, 
            templates:this.templates
        });
        this.subpages.export = new ExportKeyPageView
        ({
            filesystem:this.models.filesystem,
            accounts:this.models.accounts,
            el:this.$el.find("#page_exportAddress"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.settings = new SettingsPageView
        ({
            el: this.$el.find("#page_settings"),
            router: this.router,
            config: this.models.config,
            info: this.models.info,
            templates:this.templates
        });
        this.subpages.bitprofile = new BitprofilePageView
        ({
            clipboard: this.models.clipboard,
            filesystem:this.models.filesystem,
            registrars:this.models.registrars,
            accounts:this.models.accounts,
            fee: this.models.fee,
            profiles:this.models.profiles,
            profileValidator: this.models.profileValidator,
            syncProgress: this.models.progress,
            el:this.$el.find("#page_bitprofile"),
            router:this.router,
            templates:this.templates
        });

        this.subpages.update = new UpdatePageView
        ({
            filesystem: this.models.filesystem,
            router: this.router,
            info: this.models.info,
            config: this.models.config,
            templates: this.templates,
            el: this.$el.find("#page_update")
        });
        this.subpages.startup = new StartupPageView
        ({
            router: this.router,
            templates: this.templates,
            el: this.$el.find("#page_startup")
        });

        this.menu = new MenuView({el:this.$el.find(".mainNav")});
        this.menu.on("change", this.openPage);
        this.progress = new ProgressView({el:this.$el.find(".footer"), model:this.models.progress});
        this.network = new NetworkView({el:this.$el.find(".footer"), model:this.models.network});

        this.progress.render();
        this.network.render();
        for(var i in this.subpages) this.subpages[i].render();
        this.menuAlias = {default: "receive"};
        this.subpages["default"] = this.subpages.receive;

        this.show();
        this.checkVersion();
        this.models.info.on("change", this.checkVersion);

    },

    render: function(){
        if(this.noThrow){
            try{
                this._render();
            }catch(e){
                alert(e);
            }
        }else{
            this._render();
        }
    },

    notifyError:function(event){
        notifyError(event.message);
    },

    loaded:function(){
        this.$el.addClass("loaded");
        this.$el.find("#page_splash").addClass("off");
    },
    
    show:function(){
        this.$el.find("#page_splash").removeClass("active");
        setTimeout(this.loaded, 150);
        setTimeout(this.openPage, 1000);
    },

    checkVersion: function(){
        var info = this.models.info;
        if(info.get("xethUpdate"))
        {
            this.alertNewerVersion("New version is available");
        }
        else
        {
            if(info.get("clientUpdate"))
            {
                this.alertNewerVersion("New "+info.get("latestClient")+" available");
            }
            else
            {
                this.alertNewerVersion("");
            }
        }
    },

    alertNewerVersion:function(msg){
        var box = this.$el.find(".ver");
        box.find(".newver").html(msg);
        if(msg)
        {
            box.addClass("new");
        }
        else
        {
            box.removeClass("new");
        }
    }

});
