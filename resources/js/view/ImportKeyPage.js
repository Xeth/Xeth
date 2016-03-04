var ImportKeyPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("render", "submit");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("import");
        this.$el.html(this.template());
        this.filesystem = options.filesystem;
        this.wallet = options.wallet;
        this.$el.find(".browse a").click(this.render);
        this.$el.find(".btnSubmit").click(this.submit);
        this.fileInput = this.$el.find("#importAddress_address");
        this.router = options.router;
    },

    render:function(){
        this.filename = this.filesystem.browse({type:"open"});
        this.fileInput.val(this.filename||"");
    },

    submit:function(){
        if(!this.filename){
            notifyError("please select a file");
            return false;
        }
        var password = this.$el.find("#importAddress_password");
        if(!password.validate()){
            notifyError("password is required");
            return false;
        }
        var address = this.wallet.importKey(this.filename, password.val());
        if(!address){
            notifyError("failed to import key, file is corrupted or invalid password");
            return false;
        }
        notifySuccess("key imported");
        this.router.redirect("receive", {address: address});
        return true;
    }

});
