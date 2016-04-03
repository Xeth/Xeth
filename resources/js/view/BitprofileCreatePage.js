var BitprofileCreateFee = function(fee){
    this.estimate = function(formData){
        this.createFee = fee.estimateCreateProfile(formData.context, formData.id, formData.feeFactor);
        this.linkStealthFee = fee.estimateStealthLink(null, null, formData.feeFactor);
        return combineFee([this.createFee, this.linkStealthFee]);
    }
}

var BitprofileCreatePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "submit", "clearForm", "submitCreate", "submitStealth");
		SubPageView.prototype.initialize.call(this,options);
        this.profiles = options.profiles;
        this.feeModel = new BitprofileCreateFee(options.fee);
        this.form = options.form;
        //this.listenTo(this.profiles, "add", this.added);
    },
    
    exit:function(){
        this.form.exit();
    },

    open:function(args){
        if(!this.form.inProgress()) this.form.renderDetailsPage();
        this.form.onSubmit(this.submit);
        this.form.setFeeModel(this.feeModel);
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
        request.gas = this.feeModel.createFee.gas;
        request.price = this.feeModel.createFee.price;
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
        request.gas = this.feeModel.linkStealthFee.gas;
        request.price = this.feeModel.linkStealthFee.price;
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
