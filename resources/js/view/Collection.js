var ListView = Backbone.View.extend({
    initialize:function(options){
        _(this).bindAll("reset","append","prepend","resize","hide","show");
        if(options.scroll!==false){
            this.scroll = this.$el.mCustomScrollbar({advanced:{updateOnContentResize:true},scrollInertia:300,autoHideScrollbar:true,mouseWheel:{ normalizeDelta: false}});
            this.container = this.$el.find(".mCSB_container");
        }else{
            this.container = this.$el;
        }
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
    }
});

var CollectionView = Backbone.View.extend({

    initialize:function(options){
        this.items = {};
        this.assigned = [];
        this.factory = options.factory;
        _(this).bindAll("reset","remove","insert", "add");
        this.container = options.reversed ? new ReversedListView({el:this.$el}) : new ListView({el:this.$el});
        this.emplace = options.ordered ? this.insert : this.add;
        this.reset();
        this.collection.on("add", this.emplace);
        this.collection.on("remove", this.remove);
        this.collection.on("reset", this.reset);
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
    },

    add:function(model){
         this.container.append(this.register(this.create(model)).$el);
    },

    insert:function(model){
        var indx = this.collection.indexOf(model);
        var view = this.register(this.create(model));
        this.container.insert(view.$el, indx);

    },

    register:function(view){
        this.items[view.model? view.model.cid: view.cid] = view;
        return view;
    },

    create:function(model){
        var view = this.factory.create(model);
        view.render();
        view.$el.fadeIn(300);
        return view;
    },

    remove:function(model){
        var view = this.items[model.cid];
        if(view!=undefined){
            delete this.items[model.cid];
            view.unbind();
            view.$el.fadeOut(300,function(){
                view.remove();
            });
        }
    }

});

