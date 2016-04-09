var ListView = Backbone.View.extend({
    initialize:function(options){
        _(this).bindAll("setScroll","reset","append","prepend","resize","hide","show");
        if(options.scroll){
            this.setScroll(options.scroll);
        }
        this.container = this.$el;
    },
    setScroll:function(data){
        var scrollPage = ((data.scrollPage)? data.scrollPage : this.$el);
        var scrollbar = {   advanced:{updateOnContentResize:true},
                            scrollButtons:{enable:true},
                            theme:"light-thick",
                            scrollbarPosition:"outside",
                            scrollInertia:200
                        };
        if(data.step){
            scrollbar.scrollButtons.scrollType="stepped";
            scrollbar.keyboard={scrollType:"stepped"};
            scrollbar.mouseWheel={scrollAmount:data.step};
            scrollbar.snapAmount=data.step;
        }
        this.scroll = scrollPage.mCustomScrollbar(scrollbar);
    },
    reset:function(data){
        this.container.html("");
        if(data!=undefined){
            this.container.append(data);
        }
    },
    append:function(data){
        this.container.append(data);
    },
    prepend:function(data){
        this.container.prepend(data);
    },
    insert:function(data, indx){
        var items = this.container.children();
        if(indx<=0){
            this.container.prepend(data);
        }else if(indx>=items.length){
            this.container.append(data);
        }else{
            items.eq(indx-1).after(data);
        }
    },
    resize:function(size){
        this.$el.height(size);
    },
    hide:function(){
        this.$el.hide();
    },
    show:function(){
        this.$el.show();
    },
    focusLast:function(){
        if(this.scroll){
            this.$el.mCustomScrollbar("update");
            this.$el.mCustomScrollbar("scrollTo", "last");
        }
    },
    focusFirst:function(){
        if(this.scroll){
            this.$el.mCustomScrollbar("update");
            this.$el.mCustomScrollbar("scrollTo", "first");
        }
    }
});

var ReversedListView = ListView.extend({
    reset:function(data){
        ListView.prototype.reset.call(this,data.reverse());
        if(data.length){
            this.focusFirst();
        }
    },
    append:function(data, indx){
        ListView.prototype.prepend.call(this, data, this.container.children().length-indx);
    },
    prepend:function(data, indx){
        ListView.prototype.append.call(this, data, indx);
    },
    insert:function(data, indx){
        ListView.prototype.insert.call(this, data, this.container.children().length-indx);
    },
    resize:function(size){
        ListView.prototype.resize.call(this, size);
    },
    focusLast:function(){
        ListView.prototype.focusFirst.call(this);
    },
    focusFirst:function(){
        ListView.prototype.focusLast.call(this);
    }
});

var CollectionView = Backbone.View.extend({

    initialize:function(options){
        this.items = {};
        this.assigned = [];
        this.factory = options.factory;
        _(this).bindAll("reset","remove","insert", "add", "showEmpty", "hideEmpty", "updateEmpty");
        this.container = options.reversed ? new ReversedListView({el:this.$el, scroll:options.scroll}) : new ListView({el:this.$el, scroll:options.scroll});
        this.emplace = options.ordered ? this.insert : this.add;
        if(options.empty){
            this.$empty = $(options.empty);
            /*this.collection.on("reset", this.updateEmpty);
            this.collection.on("remove", this.updateEmpty);
            this.collection.on("add", this.updateEmpty);
            this.updateEmpty();*/
        }else{
            this.$empty = $("<div></div>");
        }
        //this.on("add", this.filterNewItem);
        //this.on("insert", this.filterNewItem);

        this.reset();

        this.collection.on("add", this.emplace);
        this.collection.on("remove", this.remove);
        this.collection.on("reset", this.reset);

    },
    hide:function(){this.$el.hide();},
    show:function(){this.$el.show();},
    toggle:function(){this.$el.toggle();},
    
    itemDisableAnimation:function(view){
        view.$el.removeClass("new");
    },
    itemEnableAnimation:function(view){
        view.$el.addClass("new");
    },
    itemShow:function(view){
        view.$el.removeClass("off");
    },
    itemHide:function(view){
        view.$el.addClass("off");
    },
    itemIsHiden:function(view){
        return view.$el.hasClass("off");
    },

    delegateEvents:function(events){
        this.each(function(view){
            view.delegateEvents(events);
        });
    },
    
    filter:function(callback){
        var itemHide = this.itemHide;
        var itemShow = this.itemShow;
        this.filterHandler = function(view){
            if(!callback(view.model)){
                itemHide(view);
                return false;
            }else{
                itemShow(view);
                return true;
            }
        }
        this.each(this.filterHandler);
        this.updateEmpty();
    },
    
    filterNewItem:function(view){
        if(this.filterHandler){
            if(this.filterHandler(view)) this.hideEmpty();
        }else{
            console.log("new hide empty",this.$el);
            this.itemShow(view);
            this.hideEmpty();
        } 
    },

    each:function(callback){
        for(var i in this.assigned){
            callback(this.assigned[i]);
        }

        for(var i in this.items){
            callback(this.items[i]);
        }
    },

    assign:function(view){
        this.assigned.push(view);
        this.container.prepend(view.$el);
    },

    find:function(callback){
        for(var i in this.assigned){
            var view = this.assigned[i];
            if(callback(view)) return view;
        }
        for(var i in this.items){
            var view = this.items[i];
            if(callback(view)) return view;
        }
        return false;
    },

    reset:function(){
        for(var i in this.items){
            this.items[i].undelegateEvents().remove();
        }
        this.items = {};
        this.collection.each(this.emplace);
        this.trigger("reset");
    },

    add:function(model){
        var view = this.register(this.create(model,true));
        this.container.append(view.$el);
        this.filterNewItem(view);
        this.trigger("add", view);
    },

    insert:function(model){
        var indx = this.collection.indexOf(model);
        var view = this.register(this.create(model,true));
        this.container.insert(view.$el, indx);
        this.filterNewItem(view);
        this.trigger("add", view);
    },

    focusLast:function(){
        this.container.focusLast();
    },

    focusFirst:function(){
        this.container.focusFirst();
    },

    register:function(view){
        this.items[view.model? view.model.cid: view.cid] = view;
        return view;
    },

    create:function(model,animate){
        var view = this.factory.create(model);
        if(animate===true){
            this.itemEnableAnimation(view);
            setTimeout(this.itemDisableAnimation,50,view);
        }
        view.render();
        return view;
    },

    remove:function(model){
        var view = this.items[model.cid];
        if(view!=undefined){
            delete this.items[model.cid];
            if(!this.itemIsHiden(view)) this.updateEmpty();            
            this.trigger("remove", view);
            view.unbind();
            this.itemEnableAnimation(view);
            setTimeout(function(){
                view.remove();
            },300);
        }
    },

    showEmpty:function(){
        this.$empty.addClass("on");
    },

    hideEmpty:function(){
        this.$empty.removeClass("on");
    },

    updateEmpty:function(){
        var empty = true;
        console.log("coll",this.collection.length,this.$empty);
        if(this.collection.length)
        {
            for(var i in this.items){
                if(!this.itemIsHiden(this.items[i]))
                {
                    empty = false;
                    break;
                }
            }
            console.log("updateEmpty check",this.$el,empty);
            (empty)?this.showEmpty():this.hideEmpty();
        }else{ 
            this.showEmpty();
            console.log("updateEmpty showEmpty",this.$el);
        }
    }

});

