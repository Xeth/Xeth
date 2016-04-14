var AccountBaseView = Backbone.View.extend({
    click:function(callback){
        var view = this;
        this.$el.on("click", function(ev){
            callback(view);
            ev.stopPropagation();
        });
    },
    unbind:function(){this.$el.unbind();},
    attach:function(dom){this.$el.appendTo(dom);},
    hide:function(){this.$el.addClass("off");},
    show:function(){this.$el.removeClass("off");},
    hidden:function(){return this.$el.hasClass("off");}
    //hidden:function(){return this.$el.hasClass("off");}
});

var AccountView = AccountBaseView.extend({
    initialize:function(options){
        _(this).bindAll("update", "shortify", "removing");
        this.template = options.template;

        var data = this.model.toJSON();
        data.balance = splitAmount(data.balance);
        this.width = options.width||55;
        this.$el = $(this.template({account: data, width:this.width}));

        this.$balance = this.$el.find(".amount");
        this.model.on("change:balance",this.update);
        this.model.on("change:unconfirmed", this.update);
        this.model.on("removing", this.removing);
    },

    removing:function(){
        this.$el.addClass("removing");
    },

    shortify:function(size, force){
        if(!size) size = 55;
        if(size==this.width&&!force) return false;
        this.width = size;
        var address = shortify(this.model.get("address"), size);
        var bitprofile = shortify(this.model.get("bitprofile"), size);
        var stealth = shortify(this.model.get("stealth"), size-bitprofile.length);
        if(!address){
            this.$el.find(".account .address").html(stealth);
            this.$el.find(".account .bitprofile .id").html(bitprofile);

        }else{
            this.$el.find(".address:first").html(address);
            this.$el.find(".origin .address").html(stealth);
            this.$el.find(".account .bitprofile .id").html(bitprofile);
        }
    },

    update:function(){
        var amount = this.model.get("balance");
        var unconfirmed = this.model.get("unconfirmed");
        if(amount!=unconfirmed){
            this.$balance.addClass("pending");
            amount = unconfirmed;
        }else{
            this.$balance.removeClass("pending");
        }
        var balance = splitAmount(amount);
        this.$balance.find(".int").html(balance.int);
        this.$balance.find(".dec").html(balance.dec);
        this.trigger("change:balance", amount);
        this.trigger("change:unconfirmed", unconfirmed);
    }
});


var AccountViewReflection = AccountView.extend({

    initialize:function(options){
        _(this).bindAll("update", "reset");
        this.width = options.width||55;
    },

    reset:function(view){
        this.undelegateEvents();
        if(this.model){
            this.stopListening(this.model);
            this.model.unpin();
        }
        this.view = view;
        if(!view){
            this.$el.html("");
        }else{
            this.model = view.model;
            this.$el.html(view.$el.clone().css("opacity", 1));
            if(this.model!=undefined){
                this.model.pin();
                this.shortify(this.width, true);
                this.$balance = this.$el.find(".amount");
                this.listenTo(view.model, "change:balance", this.update);
                this.listenTo(view.model, "change:unconfirmed", this.update);
                this.listenTo(view.model, "removing", this.removing);
                if(this.compact) this.$el.find(".amount").hide();
            }
        }
    },
    shortify:function(size){
        if(this.model) AccountView.prototype.shortify.call(this, size, true);
        this.width = size;
    },
    empty:function(){
        return this.$el.length==0||!this.view||this.view.hidden();
    },

    setCompact:function(enable){
        this.compact = enable;
        if(this.model){
            if(this.compact)
                this.$el.find(".amount").hide();
            else
                this.$el.find(".amount").show();
        }
    }

});

var NullAccountView = AccountBaseView.extend({
    initialize:function(options){
        this.template = options.templates.get("account_null");
        this.$el = $(this.template(options));
    }
});


var AccountSelectItemFactory = function(master, template){

    this.create = function(model){
        var view = new AccountView({model:model, template:template});
        view.click(master.select);
        return view;
    };

    return this;
};


var AccountSelect = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("toggle", "hide", "hideContainer", "toggleOff", "select", "parseNewItem");
        var template = options.templates.get("accounts");
        this.factory = new AccountSelectItemFactory(this, options.templates.get("account_item"));
        this.$el = $(template());
        this.dropdownBox = this.$el.find(".dropdownBox");
        this.collection = new CollectionView({factory:this.factory, collection:this.collection, el:this.dropdownBox.find(">div")});
        this.active = new AccountViewReflection({el:this.$el.find(".select")});
        this.active.click(this.toggle);
        $('html').click(this.hide);
        var empty = new NullAccountView({msg:"all accounts", templates: options.templates});
        empty.click(this.select);
        this.collection.assign(empty);
        this.collection.render();
        this.collection.on("add",this.parseNewItem);
        this.update();
    },

    style:function(style){
        if(this.css) this.$el.removeClass(this.css);
        this.css = style;
        this.$el.addClass(style);
    },

    compact:function(enable){
        this.active.setCompact(enable);
    },

    resize:function(size){
        this.active.shortify(size);
    },

    attach:function(dom){
        this.$el.appendTo(dom);
        this.readonly(false);
    },

    filter:function(callback){
        this.collection.filter(callback);
        this.update();
    },
    
    update:function(){
        var view = this.collection.find(function(view){return !view.hidden();});
        this.select(view); 
    },

    focus:function(callback){
        var _this = this;
        this.collection.each(function(view){
            if(!view.hidden() && callback(view.model)) _this.select(view);
        });
    },

    select:function(view){
        this.active.reset(view);
        this.hide();
        this.trigger("change", view?view.model:null);
    },

    toggle:function(){
        if(!this.dropdownBox.hasClass("off")){
            this.hideContainerLater();
        }else{
            this.dropdownBox.removeAttr("style");
        }
        setTimeout(this.toggleOff,0);
        //this.collection.toggle();
    },

    hide:function(ev){
        this.dropdownBox.addClass("off");
        this.hideContainerLater();
        //this.collection.hide();
        //if(ev!=undefined) ev.stopPropagation();
    },
    parseNewItem:function(view){
        if(this.active.empty()&&!view.hidden()){
            this.active.reset(view);
        }
    },
    toggleOff:function(){
        this.dropdownBox.toggleClass("off");
    },
    
    hideContainer:function(){
        this.dropdownBox.hide();
    },
    
    hideContainerLater:function(){
        setTimeout(this.hideContainer,150);
    },

    selected:function(){
        return this.active.model;
    },
    selectedView:function(){
        return this.active;
    },
    detach:function(){
        this.$el.detach();
    },
    readonly:function(enable){
        this.$el.toggleClass("readonly",enable);
    }

});
