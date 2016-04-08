var ChangePasswordPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("submit");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("change_password");
        this.router = options.router;
        
        this.accounts = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.accounts.filter(function(model){ return !!model;});
    },

    render:function(){
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
        
        this.accounts.resize();
        this.accounts.attach(this.$el.find("#editAddress_account"));
    },

    submit:function(){
        var newPassword = this.$el.find("#editAddress_newPassword");
        var repeatPassword = this.$el.find("#editAddress_newRepassword");
        var oldPassword = this.$el.find("#editAddress_password");
        if(!$([newPassword, repeatPassword, oldPassword]).validate()){
            notifyError("all fields are mandatory");
            return false;
        }

        if(newPassword.val()!=repeatPassword.val()){
            notifyError("password doesn't match");
            repeatPassword.error();
            return false;
        }

        var model = this.accounts.selected();
        if(!model.changePassword(oldPassword.val(), newPassword.val())){
            notifyError("invalid password");
            newPassword.error();
            return false;
        }
        notifySuccess("password changed");
        newPassword.val("");
        repeatPassword.val("");
        oldPassword.val("");
        this.router.redirect(); //go to default page
        return true;
    }

});
