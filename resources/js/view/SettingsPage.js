var SettingsPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll(
            "updateShowTray",
            "updateMinimizeTray",
            "updateCloseTray",
            "changeShowTray",
            "changeMinimizeTray",
            "changeCloseTray",
            "updateClientVersion"
        );
        this.config = options.config;
        this.info = options.info;
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("settings");
        this.router = options.router;
    },

    render:function(){
        this.$el.html(this.template());
        this.updateClientVersion();
        this.info.on("change", this.updateClientVersion);
        this.menu = new MenuView({el: this.$el.find(".btns")});
        this.menu.on("change", this.router.redirect);
        this.trayToggle = this.$el.find("#trayToggle");
        this.trayMinimize = this.$el.find("#trayMinimize");
        this.trayClose = this.$el.find("#trayClose");
        this.trayToggle.button({text:false});
        this.trayMinimize.button({text:false});
        this.trayClose.button({text:false});

        this.updateShowTray();
        this.updateMinimizeTray();
        this.updateCloseTray();

        this.config.on("change:tray", this.updateShowTray);
        this.config.on("change:tray_minimize", this.updateMinimizeTray);
        this.config.on("change:tray_close", this.updateCloseTray);
        this.trayToggle.on("change", this.changeShowTray);
        this.trayMinimize.on("change", this.changeMinimizeTray);
        this.trayClose.on("change", this.changeCloseTray);
        
        this.menu.render();
    },

    updateClientVersion:function(){
        var version = this.info.get("client");
        this.$el.find(".btns .ver").html(version.length > 20 ? (version.substr(0, 20)+"..."):version);
    },

    updateShowTray:function(){
        this.updateOption(this.trayToggle, "tray");
    },

    updateMinimizeTray:function(){
        this.updateOption(this.trayMinimize, "tray_minimize");
    },

    updateCloseTray:function(){
        this.updateOption(this.trayClose, "tray_close");
    },

    updateOption:function(checkbox, name){
        var opt = this.config.getFlag(name);
        if(opt!=checkbox.prop("checked"))
        {
            checkbox.prop("checked", opt);
            checkbox.button("refresh");
        }
    },

    changeShowTray:function(){
        this.changeOption(this.trayToggle, "tray");
        if(this.trayToggle.prop("checked"))
        {
            this.trayMinimize.removeAttr("disabled");
            this.trayClose.removeAttr("disabled");
        }
        else
        {
            this.trayMinimize.attr("disabled", true);
            this.trayClose.attr("disabled", true);
        }
        this.trayMinimize.button("refresh");
        this.trayClose.button("refresh");
    },

    changeMinimizeTray:function(){
        this.changeOption(this.trayMinimize, "tray_minimize");
    },

    changeCloseTray:function(){
        this.changeOption(this.trayClose, "tray_close");
    },

    changeOption:function(checkbox, name){
        var opt = checkbox.prop("checked");
        this.config.setFlag(name, opt);
    }
});
