var MenuView = Backbone.View.extend({

    initialize:function(){
        var view = this;
        this.$el.find("a").click(function(){
            var $a = $(this);
            view.trigger("change", $a.attr("rel")||$a.html());
        });
    },

    setCursor:function(name){
        this.$el.find(".active").removeClass("active");
        this.$el.find("."+name).addClass("active");
    }
});
