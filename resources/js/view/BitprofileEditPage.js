var BitprofileEditFee = function(profile,fee){
    this.estimate = function(formData){
        var editFee=[];
        if((formData.context!=profile.get("context"))||(formData.id!=profile.get("id")))
            editFee.push(fee.estimateMoveProfile(profile.get("uri"), formData.context, formData.id, formData.feeFactor));
        
        if(formData.stealth!=profile.get("payments"))
            editFee.push(fee.estimateStealthLink(profile.get("uri"), formData.stealth, formData.feeFactor));
        /*
        if((formData.name!=profile.get("name"))||(formData.avatar!=profile.get("avatar")))
            editFee.push(fee.estimateEditProfile(profile.get("uri"), "details", {name:formData.name, avatar:formData.avatar}));
            */
        return combineFee(editFee);
    }
}

var BitprofileEditPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("render", "submit", "submitEdit", "clearForm", "submitEditURI", "submitEditStealth", "submitEditDetails");
		SubPageView.prototype.initialize.call(this,options);
        this.profiles = options.profiles;
        this.feeModel = options.fee;
        this.form = options.form;
    },

    render:function(args){
        this.profile = this.profiles.get(args.uri);
        if(!this.form.inProgress()) this.form.renderDetailsPage();
        this.form.onSubmit(this.submit);
        this.form.setProfileModel(this.profile);
        this.form.setFeeModel(new BitprofileEditFee(this.profile, this.feeModel));
        this.form.resetForm();
        this.form.attach(this.$el);
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
            request.gas = this.feeModel.estimateMoveProfile(this.profile.get("uri"), request.context, request.id, request.feeFactor);
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
        
        this.listenTo(this.profiles, "error", this.clearForm);
    },

    submitEditStealth:function(skipped){
        var request = this.form.getFormData();
        if(request.stealth!=this.profile.get("payments")){
            request.gas = this.feeModel.estimateStealthLink(this.profile.get("uri"), request.stealth, request.feeFactor);
            if(!this.profile.linkStealthAddress(request)){
                this.riseError(skipped);
                return false;
            }else{
                this.form.lockPage("Changing stealth address...");
                this.listenToOnce(this.profile, "change:payments", this.clearForm);
            }
        }else{
            this.clearForm(skipped);
        }
    },

    submitEditDetails:function(skipped){
        var request = this.form.getFormData();
        if((request.name!=this.profile.get("name"))||(request.avatar!=this.profile.get("avatar"))){
            request.gas = this.feeModel.estimateEditProfile(this.profile.get("uri"), "details", {name:request.name, avatar:request.avatar});
            if(!this.profile.changeDetails(request)){
                this.riseError(skipped);
                return false;
            }else{
                this.form.lockPage("Changing profile details...");
                this.listenToOnce(this.profile, "change:details", this.clearForm);
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
