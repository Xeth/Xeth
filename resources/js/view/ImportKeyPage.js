var ImportKeyPageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("render", "submit");
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
        if(!this.wallet.importKey({password: password, file:this.filename})){
            notifyError("failed to import key, file is corrupted or invalid password");
            return false;
        }
        notifySuccess("key imported");
        router.redirect();
        return true;
    }

});
