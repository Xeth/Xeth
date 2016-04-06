
var PageRouter = function(master){
    this.redirect = function(name, args){
        master.openPage(name, args);
    }
    return this;
}

var MainWindowView = Backbone.View.extend({
    el: "body",

    initialize:function(options){
        _(this).bindAll("openPage","show","loaded", "notifyError");
        this.models = {};
        this.bindModels(options);
        this.active = null;
    },

    openPage: function(name, args){
        if(!name || name instanceof Object){
            args = name;
            name = "default";
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
            if(i=="templates") this.templates = object[i];
            else this.models[i] = object[i];
        }
    },

    render: function(){

        this.$el.prepend(this.templates.get("main_page")());

        this.models.events.onError(this.notifyError);

        this.router = new PageRouter(this);
        this.menuAlias = {default: "send"};
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
            templates:this.templates
        });
        this.subpages.bitprofile = new BitprofilePageView
        ({
            filesystem:this.models.filesystem,
            registrars:this.models.registrars,
            accounts:this.models.accounts,
            fee: this.models.fee,
            profiles:this.models.profiles,
            el:this.$el.find("#page_bitprofile"),
            router:this.router,
            templates:this.templates
        });
        this.menu = new MenuView({el:this.$el.find(".mainNav")});
        this.menu.on("change", this.openPage);
        this.progress = new ProgressView({el:this.$el.find(".footer"), model:this.models.progress});

        this.progress.render();
        for(var i in this.subpages) this.subpages[i].render();
        this.subpages["default"] = this.subpages.send;
        this.show();
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
    }

});
