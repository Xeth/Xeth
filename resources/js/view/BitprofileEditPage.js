var BitprofileEditFee = function(fee){

    var profile;

    this.setProfile = function(model){
        profile = model;
    };

    this.estimate = function(formData){
        var editFee=[];
        if((formData.context!=profile.get("context"))||(formData.id!=profile.get("id")))
        {
            this.renameFee = fee.estimateMoveProfile(profile.get("uri"), formData.context, formData.id, formData.feeFactor);
            if(this.renameFee)
            {
                editFee.push(this.renameFee);
            }
        }
        if(formData.stealth!=profile.get("payments"))
        {
            this.linkStealthFee = fee.estimateStealthLink(profile.get("uri"), formData.stealth, formData.feeFactor);
            if(this.linkStealthFee)
            {
                editFee.push(this.linkStealthFee);
            }
        }

        var details = profile.get("details")||{};
        if((formData.name!=(details.name||""))||(formData.avatar!==undefined)||(formData.ipns!=profile.get("ipns"))){
            this.editDetailsFee = fee.estimateEditProfile(profile.get("uri"), formData.feeFactor);
            if(this.editDetailsFee)
            {
                editFee.push(this.editDetailsFee);
            }
         }
        return combineFee(editFee);
    }
}

var BitprofileEditPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "submit", "submitEdit", "clearForm", "submitEditStealth", "submitEditDetails", "riseError");
		SubPageView.prototype.initialize.call(this,options);
        this.profiles = options.profiles;
        this.feeModel = options.fee;
        this.form = options.form;
        this.feeAdapter = new BitprofileEditFee(this.feeModel);
    },
    
    exit:function(){
//        this.form.exit();
    },

    open:function(args){

        this.profile = this.profiles.find({uri:args.uri});
        this.feeAdapter.setProfile(this.profile);
        this.form.onSubmit(this.submit);
        this.form.setProfileModel(this.profile);

        this.form.setFeeModel(this.feeAdapter);
        this.form.renderDetailsPage();

        this.form.attach(this.$el);
        if(!this.form.inProgress() && (!args ||args.reset!==false)){
            this.form.resetForm();
        }
        if(args && args.address){
            this.form.selectAccount("stealth", args.address);
        }


    },

    submit:function(){
        if(this.form.hasLowFee()){
            feeWarning(this.submitEdit);
        }
        else{
            setTimeout(this.submitEdit, 0);
        }
    },

    submitEdit:function(){
        this.stopListening(this.profile);
        this.form.lockPage("Applying changes...");
        this.listenToOnce(this.profile, "error", this.riseError);
        this.submitEditURI();
    },

    submitEditURI:function(){
        var request = this.form.getFormData();
        if((request.context!=this.profile.get("context"))||(request.id!=this.profile.get("id"))){
            if(this.feeAdapter.renameFee)
            {
                request.gas = this.feeAdapter.renameFee.gas;
                request.price = this.feeAdapter.renameFee.price;
            }
            if(!this.profile.changeURI(request)){
                this.form.riseError();
                return false;
            }else{
                this.form.setLockMessage("Changing URI...");
                this.listenToOnce(this.profile, "change:uri", this.submitEditStealth);
            }
        }else{
            this.submitEditStealth(true);
        }
    },

    submitEditStealth:function(skipped){
        var request = this.form.getFormData();
        if(request.stealth!=this.profile.get("payments")){
            if(this.feeAdapter.linkStealthFee)
            {
                request.gas = this.feeAdapter.linkStealthFee.gas;
                request.price = this.feeAdapter.linkStealthFee.price;
            }
            if(!this.profile.linkStealthAddress(request)){
                this.riseError();
                return false;
            }else{
                this.form.setLockMessage("Changing stealth address...");
                this.listenToOnce(this.profile, "change:payments", this.submitEditDetails);
            }
        }else{
            this.submitEditDetails(skipped);
        }
    },

    submitEditDetails:function(skipped){
        var formData = this.form.getFormData();
        var details = this.profile.get("details")||{};
        if((formData.name!=(details.name||""))||(formData.avatar!==undefined)||(formData.ipns!=this.profile.get("ipns"))){
            var request = {ipns:formData.ipns, password:formData.password, details:{}};

            if(this.feeAdapter.editDetailsFee)
            {
                request.gas = this.feeAdapter.editDetailsFee.gas;
                request.price = this.feeAdapter.editDetailsFee.price;
            }

            if(formData.name!=details.name){
                request.details.name = formData.name.length?formData.name:null; //null to remove
            }
            if(formData.avatar!==undefined)
            {
                request.details.avatar = formData.avatar;
            }
            if(!this.profile.changeDetails(request)){
                this.riseError();
                return false;
            }else{
                this.form.setLockMessage("Changing profile details...");
                this.listenToOnce(this.profile, "change:details", this.clearForm);
            }
        }else{
            this.clearForm(skipped);
        }
    },

    clearForm:function(skipped){
        this.stopListening(this.profile);
        if(skipped===true) notifySuccess("There is nothing to change");
        this.form.reset();
    },

    riseError:function(){
        this.form.unlockPage();
        this.form.risePasswordError();
    }

});
