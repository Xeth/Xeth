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

        this.reset();

        this.collection.on("add", this.emplace);
        this.collection.on("remove", this.remove);
        this.collection.on("reset", this.reset);
        if(options.empty){
            this.$empty = $(options.empty);
            this.collection.on("reset", this.updateEmpty);
            this.collection.on("remove", this.updateEmpty);
            this.collection.on("add", this.updateEmpty);
            this.updateEmpty();
        }

    },
    hide:function(){this.$el.hide();},
    show:function(){this.$el.show();},
    toggle:function(){this.$el.toggle();},

    delegateEvents:function(events){
        this.each(function(view){
            view.delegateEvents(events);
        });
    },

    filter:function(callback){
        this.each(function(view){
            if(callback(view.model))
                view.$el.show();
            else
                view.$el.hide();
        });
        this.updateEmpty();
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
        var view = this.register(this.create(model));
        this.container.append(view.$el);
        this.trigger("add", view);
    },

    insert:function(model){
        var indx = this.collection.indexOf(model);
        var view = this.register(this.create(model));
        this.container.insert(view.$el, indx);
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

    create:function(model){
        var view = this.factory.create(model);
        view.$el.hide();
        view.render();
        setTimeout(function(){
            view.$el.removeClass("off");
        },50);
        return view;
    },

    remove:function(model){
        var view = this.items[model.cid];
        if(view!=undefined){
            delete this.items[model.cid];
            this.trigger("remove", view);
            view.unbind();
            view.$el.addClass("off");
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

    updateEmpty:function(val){
        var empty = true;
        if(this.collection.length)
        {
            this.each(function(view){
                if(!view.$el.is(":hidden"))
                {
                    empty = false;
                }
            });
            (empty)?this.showEmpty():this.hideEmpty();
        }
        else this.showEmpty();
    }

});

