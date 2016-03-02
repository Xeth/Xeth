
var PageRouter = function(master){
    this.redirect = function(name, args){
        master.open(name, args);
    }
    return this;
}

var MainWindowView = Backbone.View.extend({
    el: "body",

    initialize:function(options){
        _(this).bindAll("open");
        this.models = {};
        this.models.addressbook = options.addressbook;
        this.models.accounts = options.accounts;
        this.models.clipboard = options.clipboard;
        this.models.filesystem = options.filesystem;
        this.models.transactions = options.transactions;
        this.models.progress = options.progress;

        this.templates = options.templates;
    },

    open: function(name, args){
        if(!name || name instanceof Object){
            args = name;
            name = "default";
        }
        var view =  this.subpages[name];
        if(view!=undefined){
            this.$el.find(".page.active").removeClass("active");
            view.$el.removeClass("off").addClass("active");
            this.menu.setCursor(this.menuAlias[name]||name);
            view.render(args);
        }
    },

    bindModels:function(object){
        for(var i in object){
            if(i=="templates") this.templates = object[i];
            else this.models[i] = object[i];
        }
    },

    render: function(){

        this.$el.find("#page_splash").removeClass("active").addClass("off");
        this.$el.html(this.templates.get("main_page")());
        this.$el.addClass("loaded");

        this.accounts = new AccountSelect({collection:this.models.accounts, templates:this.templates});
        this.router = new PageRouter(this);
        this.menuAlias = {default: "receive"};
        this.subpages = {};
        this.subpages.send = new SendPageView
        ({
            accounts: this.accounts, 
            addressbook:this.models.addressbook, 
            el:this.$el.find("#page_send"), 
            router:this.router, 
            clipboard: this.models.clipboard,
            templates:this.templates
        });
        this.subpages.receive = new ReceivePageView
        ({
            accounts:this.accounts, 
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
            accounts:this.accounts,
            transactions:this.models.transactions,
            el:this.$el.find("#page_transactions"),
            templates:this.templates
        });
        this.subpages.password = new ChangePasswordPageView
        ({
            accounts:this.accounts,
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
            accounts:this.accounts,
            el:this.$el.find("#page_exportAddress"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.settings = new SettingsPageView
        ({
            el:this.$el.find("#page_settings"),
            router:this.router,
            templates:this.templates
        });
        this.subpages["default"] = this.subpages.receive;
        this.menu = new MenuView({el:this.$el.find(".mainNav")});
        this.menu.on("change", this.open);
        this.progress = new ProgressView({el:this.$el.find(".footer"), model:this.models.progress});

        this.progress.render();
        setTimeout(this.open, 800);
    }

});
