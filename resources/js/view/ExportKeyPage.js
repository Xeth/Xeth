var ExportKeyPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("submit");
		SubPageView.prototype.initialize.call(this,options);
        this.filesystem = options.filesystem;
        this.accounts = options.accounts;
        this.template = options.templates.get("export");
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
        this.router = options.router;
    },

    render:function(){
        this.accounts.attach(this.$el.find("#exportAddress_account"));
        this.accounts.filter(function(model){ return model!=undefined;});
        this.accounts.style("send");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
    },

    submit:function(){
        var path = this.filesystem.browse();
        var model = this.accounts.selected();
        if(!model.backup(path)){
            notifyError("failed to backup, please check disk space");
            return false;
        }
        notifySuccess("key exported");
        this.router.redirect(); //go to default page
        return true;
    }

});
