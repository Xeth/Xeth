var ImportKeyPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "render", "submit", "browse", "importKey");
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
        this.password = this.$el.find("#importAddress_password");
    },

    open:function(){
        setTimeout(this.browse, 500);
    },

    browse:function(){
        var filename = this.filesystem.browse({type:"open"});
        if(filename) this.fileInput.val(filename);
    },

    submit:function(){
        var filename = this.fileInput.val();
        if(!filename){
            notifyError("please select a file");
            return false;
        }
        if(!this.password.validate()){
            notifyError("password is required");
            return false;
        }
        this.$el.find(".formpage").addClass("waiting");
        setTimeout(this.importKey, 0, filename);
    },
    importKey: function(filename){
        var address = this.wallet.importKey(filename, this.password.val());
        this.$el.find(".formpage").removeClass("waiting");
        if(!address){
            notifyError("failed to import key, file is corrupted or invalid password");
            return false;
        }
        notifySuccess("key imported");
        this.password.val("");
        this.fileInput.val("");
        this.router.redirect("receive", {address: address});
        return true;
    }

});
