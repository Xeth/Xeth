var SettingsPageView = Backbone.View.extend({

    initialize:function(options){
        this.template = _.template($("#settings_tpl").html());
        this.$el.html(this.template());
        this.menu = new MenuView({el: this.$el.find(".btns")});
        this.menu.on("change", options.router.changePage);
    },

    render:function(){
        this.menu.render();
    }
});
