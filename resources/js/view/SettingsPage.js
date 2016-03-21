var SettingsPageView = SubPageView.extend({

    initialize:function(options){
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("settings");
        this.$el.html(this.template());
        this.menu = new MenuView({el: this.$el.find(".btns")});
        this.menu.on("change", options.router.redirect);
        this.trayToggle = this.$el.find("#trayToggle");
        this.trayMinimize = this.$el.find("#trayMinimize");
        this.trayClose = this.$el.find("#trayClose");
        this.trayToggle.button({text:false});
        this.trayMinimize.button({text:false});
        this.trayClose.button({text:false});
    },

    render:function(){
        this.menu.render();
    }
});
