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
    hide:function(){this.$el.hide().addClass("off");},
    show:function(){this.$el.show().removeClass("off");},
    hidden:function(){return this.$el.hasClass("off");}
});

var AccountView = AccountBaseView.extend({
    initialize:function(options){
        _(this).bindAll("update");
        this.template = options.template;

        var data = this.model.toJSON();
        data.balance = splitAmount(data.balance);
        this.width = options.width||55;
        this.$el = $(this.template({account: data, width:this.width}));

        this.$balance = this.$el.find(".amount");
        this.model.on("change:balance", this.update);
    },

    shortify:function(size, force){
        if(!size) size = 55;
        if(size==this.width&&!force) return;
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
        var balance = splitAmount(this.model.get("balance"));
        this.$balance.find(".int").html(balance.int);
        this.$balance.find(".dec").html(balance.dec);
    }
});


var AccountViewReflection = AccountView.extend({

    initialize:function(options){
        _(this).bindAll("update");
        this.width = options.width||55;
    },

    reset:function(view){
        this.undelegateEvents();
        this.view = view;
        if(!view){
            this.$el.html("");
        }else{
            this.model = view.model;
            this.$el.html(view.$el.clone().css("opacity", 1));
            if(this.model!=undefined){
                this.shortify(this.width, true);
                this.$balance = this.$el.find(".amount");
                this.listenTo(view.model, "change:balance", this.update);
                if(this.compact) this.$el.find(".amount").hide();
            }
        }
    },
    shortify:function(size){
        if(this.model) AccountView.prototype.shortify.call(this, size, true);
        this.width = size;
    },

    setCompact:function(enable){
        this.compact = enable;
        if(this.model){
            if(this.compact)
                this.$el.find(".amount").hide()
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
    }

    return this;
};


var AccountSelect = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("toggle","hide", "select");
        var template = options.templates.get("accounts");
        this.factory = new AccountSelectItemFactory(this, options.templates.get("account_item"));
        this.$el = $(template());
        this.collection = new CollectionView({factory:this.factory, collection:this.collection, el:this.$el.find(".dropdownBox>div")});
        this.active = new AccountViewReflection({el:this.$el.find(".select")});
        this.active.click(this.toggle);
        $('html').click(this.hide);
        var empty = new NullAccountView({msg:"all accounts", templates: options.templates});
        empty.click(this.select);
        this.collection.assign(empty);
        this.collection.render();
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
    },

    filter:function(callback){
        this.collection.each(function(view){
            if(!callback(view.model)) view.hide(); else view.show();
        });
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
        this.collection.hide();
        this.trigger("change", view?view.model:null);
    },

    toggle:function(){
        this.collection.toggle();
    },

    hide:function(ev){
        this.collection.hide();
        //if(ev!=undefined) ev.stopPropagation();
    },

    selected:function(){
        return this.active.model;
    }

});
