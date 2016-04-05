var BitprofileEditFee = function(profile,fee){
    this.estimate = function(formData){
        var editFee=[];
        if((formData.context!=profile.get("context"))||(formData.id!=profile.get("id")))
        {
            this.renameFee = fee.estimateMoveProfile(profile.get("uri"), formData.context, formData.id, formData.feeFactor);
            editFee.push(this.renameFee);
        }
        if(formData.stealth!=profile.get("payments"))
        {
            this.linkStealthFee = fee.estimateStealthLink(profile.get("uri"), formData.stealth, formData.feeFactor);
            editFee.push(this.linkStealthFee);
        }
        if((formData.name!=profile.get("name"))||(formData.avatar!=profile.get("avatar"))){
            this.editDetailsFee = fee.estimateEditProfile(profile.get("uri"), {name:formData.name, avatar:formData.avatar});
            editFee.push(this.editDetailsFee);
         }
        return combineFee(editFee);
    }
}

var BitprofileEditPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "submit", "submitEdit", "clearForm", "submitEditURI", "submitEditStealth", "submitEditDetails");
		SubPageView.prototype.initialize.call(this,options);
        this.profiles = options.profiles;
        this.feeModel = options.fee;
        this.form = options.form;
    },
    
    exit:function(){
        this.form.exit();
    },

    open:function(args){
        this.profile = this.profiles.find({uri:args.uri});
        if(!this.form.inProgress()){
            this.form.renderDetailsPage();
        }
        this.form.onSubmit(this.submit);
        this.form.setProfileModel(this.profile);
        this.feeAdapter = new BitprofileEditFee(this.profile, this.feeModel);
        this.form.setFeeModel(this.feeAdapter);
        this.form.attach(this.$el);
        if(!this.form.inProgress()){
            this.form.resetForm();
        }
    },

    submit:function(){
        if(this.form.hasLowFee()){
            feeWarning(this.submitEditURI);
        }
        else{
            setTimeout(this.submitEditURI, 0);
        }
    },

    submitEdit:function(){
        var request = this.form.getFormData();
        if((request.context!=this.profile.get("context"))||
           (request.id!=this.profile.get("id"))||
           (request.stealth!=this.profile.get("payments"))||
           (request.name!=this.profile.get("name"))||
           (request.avatar!=this.profile.get("avatar"))){
            
            this.form.lockPage("Applying changes...");
            this.submitEditURI();
        }else{
            notifySuccess("There is nothing to change");
        }
    },

    submitEditURI:function(){
        var request = this.form.getFormData();
        if((request.context!=this.profile.get("context"))||(request.id!=this.profile.get("id"))){
            request.gas = this.feeAdapter.renameFee.gas;
            request.price = this.feeAdapter.renameFee.price;
            if(!this.profile.changeURI(request)){
                this.form.risePasswordError();
                this.form.unlockPage();
                return false;
            }else{
                this.form.lockPage("Changing URI...");
                this.listenToOnce(this.profile, "change:uri", this.submitEditStealth);
            }
        }else{
            this.submitEditStealth(true);
        }
        
        this.listenTo(this.profile, "error", this.clearForm);
    },

    submitEditStealth:function(skipped){
        var request = this.form.getFormData();
        if(request.stealth!=this.profile.get("payments")){
            request.gas = this.feeAdapter.linkStealthFee.gas;
            request.price = this.feeAdapter.linkStealthFee.price;
            if(!this.profile.linkStealthAddress(request)){
                this.riseError(skipped);
                return false;
            }else{
                this.form.lockPage("Changing stealth address...");
                this.listenToOnce(this.profile, "change:payments", this.submitEditDetails);
            }
        }else{
            this.clearForm(skipped);
        }
    },

    submitEditDetails:function(skipped){
        var formData = this.form.getFormData();
        var profileName = this.profile.get("name");
        var profileAvatar = this.profile.get("avatar");
        if((formData.name!=profileName)||(formData.avatar!=profileAvatar)){
            var request = {gas: this.feeAdapter.editDetailsFee.gas, price:this.feeAdapter.editDetailsFee.price, details:{}};
            if(formData.name!=profileName)){
                request.details.name = formData.name.length?formData.name:null; //null to remove
            }
            if(formData.avatar!=profileAvatar){
                request.details.avatar = formData.avatar.length?formData.avatar:null;
            }
            if(!this.profile.changeDetails(request)){
                this.riseError(skipped);
                return false;
            }else{
                this.form.lockPage("Changing profile details...");
                this.listenToOnce(this.profile, "change:details", this.submitEditDetails);
            }
        }else{
            this.clearForm(skipped);
        }
    },
    clearForm:function(skipped){
        if(skipped===true) notifySuccess("There is nothing to change");
        this.form.reset();
        this.stopListening(this.profile);
    },
    riseError:function(skipped){
        this.form.unlockPage();
        if(skipped===true){
            this.form.risePasswordError();
        }else{
            this.clearForm();
        }
    }

});
