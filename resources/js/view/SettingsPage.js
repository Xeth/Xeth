var SettingsPageView = SubPageView.extend({

    initialize:function(options){
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("settings");
        this.$el.html(this.template());
        this.menu = new MenuView({el: this.$el.find(".btns")});
        this.menu.on("change", options.router.redirect);
    },

    render:function(){
        this.menu.render();
    }
});
