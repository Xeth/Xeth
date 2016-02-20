var ChangePasswordPageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("submit");
        this.accounts = options.accounts;
        this.template = _.template($("#change_password_tpl").html());
        this.$el.html(this.template());
        this.$el.find(".btnSubmit").click(this.submit);
    },

    render:function(){
        this.accounts.filter(function(model){ return !!model;});
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
            newPassword.error();
            repeatPassword.error();
            return false;
        }


        var model = this.accounts.selected();
        if(!model.changePassword({previous: oldPassword.val(), password:newPassword.val()})){
            notifyError("invalid password");
            return false;
        }
        notifySuccess("password changed");
        this.trigger("done");
        return true;
    }

});
