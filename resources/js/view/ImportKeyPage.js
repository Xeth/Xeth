var ImportKeyPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "render", "submit", "browse");
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("import");
        this.filesystem = options.filesystem;
        this.wallet = options.wallet;
        this.router = options.router;
    },

    render:function(){
        this.$el.html(this.template());
        this.$el.find(".browse a").click(this.browse);
        this.$el.find(".btnSubmit").click(this.submit);
        this.fileInput = this.$el.find("#importAddress_address");
    },

    open:function(){
        setTimeout(this.browse, 500);
    },

    browse:function(){
        this.filename = this.filesystem.browse({type:"open"});
        if(this.filename)this.fileInput.val(this.filename);
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
