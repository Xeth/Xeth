var NetworkView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("update");
        this.$icon = this.$el.find(".icons .network");
    },

    render:function(){
        this.update();
        this.model.on("change:peers", this.update);
    },

    update:function(){
        var peers = this.model.get("peers");
        if(peers < 5) this.$icon.removeClass("ok");
        else{
            if(!this.$icon.hasClass("ok")) this.$icon.addClass("ok");
        } 
        this.$icon.attr("title", "peers "+peers);
    }
});
