
var PageRouter = function(master){
    this.redirect = function(name, args){
        master.open(name, args);
    }
}

var MainWindowView = Backbone.View.extend({
    el: "body",

    initialize:function(options){
        _(this).bindAll("open");
        this.templates = options.templates;

        this.accounts = new AccountSelect({collection:options.accounts, templates:templates});
        this.router = new PageRouter(this);

        this.menuAlias = {default: "receive"};
        this.subpages = {};
        this.subpages.send = new SendPageView
        ({
            accounts: this.accounts, 
            addressbook:options.addressbook, 
            el:this.$el.find("#page_send"), 
            router:this.router, 
            clipboard: options.clipboard,
            templates:this.templates
        });
        this.subpages.receive = new ReceivePageView
        ({
            accounts:this.accounts, 
            clipboard: options.clipboard, 
            el:this.$el.find("#page_receive"), 
            templates:this.templates,
            router:this.router
        });
        this.subpages.addressbook = new AddressBookPageView
        ({
            addressbook:options.addressbook,
            el:this.$el.find("#page_addressbook"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.transactions = new TransactionsPageView
        ({
            accounts:this.accounts,
            transactions:options.transactions,
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
            accounts:options.accounts,
            el:this.$el.find("#page_newAddress"),
            router:this.router,
            templates:this.templates
        });
        this.subpages.import = new ImportKeyPageView
        ({
            filesystem:options.filesystem,
            wallet:options.accounts,
            el:this.$el.find("#page_importAddress"),
            router:this.router, 
            templates:this.templates
        });
        this.subpages.export = new ExportKeyPageView
        ({
            filesystem:options.filesystem,
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
        this.progress = new ProgressView({el:this.$el.find(".footer"), progress:options.progress});
    },

    open: function(name, args){
        this.$el.find(".page.active").removeClass("active");
        if(!name || name instanceof Object){
            args = name;
            name = "default";
        }
        var view =  this.subpages[name];
        view.$el.removeClass("off").addClass("active");
        this.menu.setCursor(this.menuAlias[name]||name);
        view.render(args);
    },

    render: function(){
        this.$el.find("#page_splash").removeClass("active").addClass("off");
        this.$el.addClass("loaded");
        setTimeout(this.open, 800);
    }

});
