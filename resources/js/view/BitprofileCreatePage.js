var BitprofileCreateFee = function(fee){
    this.estimate = function(formData){
        return combineFee([fee.estimateCreateProfile(formData.context, formData.id), fee.estimateEditProfile(formData.context+":"+formData.id, "payments", formData.stealth)]);
    }
}

var BitprofileCreatePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("render", "submit", "clearForm", "submitCreate", "submitStealth");
		SubPageView.prototype.initialize.call(this,options);
        this.profiles = options.profiles;
        this.feeModel = options.fee;
        this.form = options.form;
        //this.listenTo(this.profiles, "add", this.added);
    },

    render:function(args){
        if(!this.form.inProgress()) this.form.renderDetailsPage();
        this.form.onSubmit(this.submit);
        this.form.setFeeModel(new BitprofileCreateFee(this.feeModel));
        this.form.resetForm();
        this.form.attach(this.$el);
    },

    submit:function(){
        if(this.form.hasLowFee()){
            feeWarning(this.submitCreate);
        }
        else{
            setTimeout(this.submitCreate, 0);
        }
    },

    submitCreate:function(){
        var request = this.form.getFormData();
        request.gas = this.feeModel.estimateCreateProfile(request.context, request.id);
        if(!this.profiles.create(request)){
            this.form.risePasswordError();
            return false;
        }
        this.listenToOnce(this.profiles, "error", this.clearForm);
        //notifySuccess("creating bitprofile");
        this.form.lockPage("Registration in progress...");
        this.listenToOnce(this.profiles, "add", this.submitStealth);
        return true;
    },
    submitStealth:function(){
        var request = this.form.getFormData();
        request.gas = this.feeModel.estimateEditProfile(request.context+":"+request.id, "payments", request.stealth);
        this.form.setLockMessage("Linking stealth address...");
        var profile = this.profiles.first();
        if(!profile.linkStealthAddress(request)){
            this.form.unlockPage();
            return false;
        }else{
            profile.once("change:payments", this.clearForm);  
        }
    },
    clearForm:function(){
        this.form.reset();
        this.stopListening(this.profiles);
    }

});
