var ExportKeyPageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("submit");
        this.filesystem = options.filesystem;
        this.accounts = options.accounts;
        this.template = options.templates.get("export");
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
    },

    render:function(){
        this.accounts.filter(function(model){ return !!model;});
        this.accounts.resize();
        this.accounts.attach(this.$el.find("#exportAddress_account"));
    },

    submit:function(){
        var path = this.filesystem.browse();
        var model = this.accounts.selected();
        if(!model.backup(path)){
            notifyError("failed to backup, please check disk space");
            return false;
        }
        notifySuccess("key exported");
        this.trigger("done");
        return true;
    }

});
