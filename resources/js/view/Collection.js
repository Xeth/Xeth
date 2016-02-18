var CollectionView = Backbone.View.extend({

    initialize:function(options){
        this.items = {};
        this.factory = options.factory;
        if(options.scroll){}
        _(this).bindAll("reset","remove","insert", "add");
    },

    render:function(){
        this.reset();
        this.collection.on("add", this.insert);
        this.collection.on("remove", this.remove);
        this.collection.on("reset", this.reset);
    },

    delegateEvents:function(events){
        this.each(function(view){
            view.delegateEvents(events);
        });
    },

    each:function(callback){
        for(var i in this.items){
            callback(this.items[i]);
        }
    },

    reset:function(){
        this.$el.html("");
        this.collection.each(this.add);
    },

    add:function(model){
        this.$el.append(this.register(model).$el);
    },

    insert:function(model){
        var indx = this.model.indexOf(model);
        var view = this.register(model);

        var items = this.$el.children();
        if(indx<=0){
            this.$el.prepend(view.$el);
        }else if(indx>=items.length){
            this.$el.append(view.$el);
        }else{
            items.eq(indx-1).after(view.$el);
        }
    },

    register:function(model){
        var view = this.factory.create(model);
        this.items[model.cid] = view;
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

