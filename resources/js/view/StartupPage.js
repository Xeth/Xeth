var StartupPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("render", "submit");
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("startup");
        this.router = options.router;
    },

    render:function(){
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
    },

    submit:function(){
        this.router.redirect("settings");
    }

});
