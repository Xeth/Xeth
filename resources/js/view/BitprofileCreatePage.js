var BitprofileCreateFee = function(fee){
    this.estimate = function(formData){
        this.createFee = fee.estimateCreateProfile(formData.context, formData.id, formData.feeFactor);
        this.linkStealthFee = fee.estimateStealthLink(null, null, formData.feeFactor);
        var fees = [this.createFee, this.linkStealthFee];
        if(formData.avatar||formData.name){
            this.detailsFee = fee.estimateEditProfile(null);
            fees.push(this.detailsFee);
        }
        return combineFee(fees);
    }
}

var BitprofileCreatePageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "submit", "clearForm", "submitCreate", "submitStealth", "submitDetails", "riseError");
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
        this.form.attach(this.$el);

        if(args && args.address){
            this.form.selectAccount("stealth", args.address);
        }
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
            this.riseError();
            return false;
        }
        this.listenToOnce(this.profiles, "error", this.riseError);
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
            this.riseError();
            return false;
        }else{
            profile.once("change:payments", this.submitDetails);
        }
    },
    submitDetails:function(){
        var formData = this.form.getFormData();
        if(formData.avatar||formData.name)
        {
            var request = {gas: this.feeModel.detailsFee.gas, price:this.feeModel.detailsFee.price, ipns:formData.ipns, password:formData.password, details:{}};
            if(formData.avatar) request.details.avatar = formData.avatar;
            if(formData.name) request.details.name = formData.name;
            var profile = this.profiles.first();
            if(!profile.changeDetails(request)){
                this.riseError();
                return false;
            }else{
                this.form.lockPage("Changing profile details...");
                this.listenToOnce(profile, "change:details", this.clearForm);
            }
        }
        else
        {
            this.clearForm();
        }
    },
    clearForm:function(){
        this.form.reset();
        this.stopListening(this.profiles);
    },

    riseError:function(){
        this.form.unlockPage();
        this.form.renderPaymentPage();
        this.form.risePasswordError();
    }
});
