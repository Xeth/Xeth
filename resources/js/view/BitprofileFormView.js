var BitprofileFormView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll(
            "computeFee",
            "clickGenerate",
            "clickBrowseAvatar",
            "clickRemoveAvatar",
            "submitDetails",
            "submit",
            "resetForm",
            "reset",
            "lockPage",
            "validateName",
            "renderDetailsPage",
            "resetAddressError",
            "updatePaymentAccountBalance",
            "checkSyncStatus"
        );
        SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("bitprofile_form");
        this.registrars = options.registrars;
        this.router = options.router;
        this.filesystem = options.filesystem;
        this.profileValidator = options.profileValidator;
        this.syncProgress = options.syncProgress;

        this.pending = false;
        this.avatarDeleted = false;
        this.locks = 0;
        
        this.account_details = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.account_payment = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.account_details.filter(function(model){return model!=undefined&&!model.get("address")&&model.get("stealth");});
        this.account_payment.filter(function(model){return model!=undefined&&model.get("address");});
    },

    render:function(){
        this.$el = $('<div class="bitprofileForm">'+this.template()+'</div>');
        this.detailsPage = this.$el.find("#bitporfileCreate_details");
        this.paymentPage = this.$el.find("#bitporfileCreate_payment");
        
        this.feeFactor = new FeeSlider({el:this.$el.find(".section_fee")});
        this.feeFactor.on("change", this.computeFee);
        
        this.IPNSOption = this.$el.find("#IPNS");
        this.IPNSOption.button({text:false});
        
        this.password = this.$el.find("#bitprofileCreate_password");
        this.bitprofileId = this.$el.find("#bitprofileCreate_id");
        this.name = this.detailsPage.find("input.name");
        this.avatar = this.detailsPage.find("input.avatarURL");
        this.avatarImage = this.detailsPage.find(".avatar img");
        this.avatarRemove = this.detailsPage.find(".btnRemove");
        this.accountSelect_details = this.$el.find("#bitprofileCreateStealthList");
        this.accountSelect_payment = this.$el.find("#bitprofileCreateAccountList");
        this.accountBalance_payment = this.$el.find("#bitprofileCreateAccountBalance");
        this.$form = this.paymentPage.find(".formpage");
        this.bitprofileContext = this.$el.find("#bitporfileCreate_context");
        this.renderRegistrars();
        this.bitprofileContext.selectmenu().selectmenu( "widget" ).addClass( "contextSelect" );
        this.$el.find("#bitporfileCreate_details .btnSubmit").click(this.submitDetails);
        this.$el.find("#bitporfileCreate_payment .btnSubmit").click(this.submit);
        this.$el.find("#bitporfileCreate_details .submitCancel").click(this.resetForm);
        this.$el.find("#bitporfileCreate_payment .submitCancel").click(this.renderDetailsPage);
        this.$el.find(".generate a").click(this.clickGenerate);
        this.bitprofileId.on("input", this.validateName);
        this.avatar.click(this.clickBrowseAvatar);
        this.avatarRemove.click(this.clickRemoveAvatar);
        this.avatarRemove.hide();
        
        this.account_payment.selectedView().on("change:balance", this.updatePaymentAccountBalance);
        this.account_payment.on("change", this.resetAddressError);
        this.account_payment.on("change", this.updatePaymentAccountBalance);
        
        this.$el.find('.inputBtn').tooltip({
            position: { my: "center bottom", at: "center top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        if(this.syncProgress.get("sync")<99.99)
        {
            this.lockPage("synchronizing with network");
            this.listenTo(this.syncProgress, "change:sync", this.checkSyncStatus);
        }
        
        this.account_details.resize(20);
        this.account_details.compact(true);
        this.account_details.attach(this.accountSelect_details);
        this.account_details.style("mini receive");
        
        this.account_payment.resize(25);
        this.account_payment.compact(true);
        this.account_payment.attach(this.accountSelect_payment);
        this.account_payment.style("mini send");
    },

    checkSyncStatus:function(){
        if(this.syncProgress.get("sync")>=99.99)
        {
            this.stopListening(this.syncProgress);
            this.renderRegistrars();
            this.unlockPage();
        }
    },
    
    renderRegistrars:function(){
        this.bitprofileContext.html("");
        if(this.registrars.length==0) this.bitprofileContext.append("<option>NONE</option>");
        else
        for(var i=0; i<this.registrars.length; i++)
        {
            var registrar = this.registrars.at(i);
            this.bitprofileContext.append("<option>"+registrar.get("uri")+"</option>");
        }
    },

    attach:function(dom){
        this.$el.appendTo(dom);
    },

    onSubmit:function(callback){
        this.submitStrategy = callback;
    },

    setFeeModel:function(feeModel){
        this.feeModel = feeModel;
    },

    setProfileModel:function(profileModel){
        if(this.model) this.stopListening(this.model);
        this.model = profileModel;
    },
    
    validateName:function(){
        var name = this.bitprofileId.val().toLowerCase();
        
        if(this.inProgress()||this.model&&this.model.get("context")==this.bitprofileContext.val()&&this.model.get("id")==name){
            this.bitprofileId.clearvalid();
            this.bitprofileId.noerror();
        }else{
            if(name.length<3){
                this.setIDError("3 chars minimum");
                return false;   
            }
            if(!this.profileValidator.isValidName(name)){
                this.setIDError("use only ( A-Z, 0-9, _ )");
                return false;   
            }
            if(!this.profileValidator.isAvailable({id:name, context:this.bitprofileContext.val()})){
                this.setIDError("already taken");
                return false;
            }
            this.bitprofileId.valid();
        }
        return true;
    },

    setIDError:function(msg){
        this.bitprofileId.error(msg);
    },

    clickGenerate:function(){
        var request = {stealth: true, redirect:"bitprofile", redirectArgs:{subpage:"form"}};
        request.redirectArgs.args = (this.model)? {uri:this.model.get("uri")} : {};
        request.redirectArgs.args.reset = false;
        this.router.redirect("generate", request);
    },

    clickBrowseAvatar:function(){
        var filename = this.filesystem.browse({type:"open", extensions:"Image (*.jpg *.jpeg *.png *.bmp *.tif)"});
        if(filename){
            this.avatar.val(filename);
            var image = this.filesystem.readImage(filename);
            this.avatarImage.attr("src", image);
            this.avatarDeleted = false;
            this.avatarRemove.show();
        }
    },

    clickRemoveAvatar:function(){
        this.avatar.val("");
        this.avatarDeleted = true;
        this.avatarImage.attr("src",'img/avatarEmpty.png');
        this.avatarRemove.hide();
    },

    renderDetailsPage:function(){
        this.detailsPage.addClass("active");
        this.paymentPage.removeClass("active");
    },

    renderPaymentPage:function(){
        if(this.model){
            var account = this.model.get("account");
            this.account_payment.readonly(true);
            this.account_payment.focus(function(model){ return (model)&&(model.get("address"))==account});
        }
        this.computeFee();
        this.updatePaymentAccountBalance();
        this.detailsPage.removeClass("active");
        this.paymentPage.addClass("active");
    },

    updatePaymentAccountBalance:function(){
        var balance = splitAmount(this.account_payment.selected().get("balance"));
        this.accountBalance_payment.find(".int").html(balance.int);
        this.accountBalance_payment.find(".dec").html(balance.dec);
    },

    resetAddressError: function(){
        this.accountSelect_payment.noerror();
    },

    reset:function(){
        this.renderDetailsPage();
        this.resetForm();
        this.unlockPage();
    },

    resetForm:function(){
        this.resetAddressError();
        this.bitprofileId.noerror();
        this.bitprofileId.clearvalid();
        this.password.noerror();
        this.password.val("");
        this.avatarDeleted = false;
        this.fillForm();  
    },

    fillForm:function(){
        if(this.model){
            var account = this.model.get("payments");
            this.bitprofileContext.val(this.model.get("context"));
            this.bitprofileId.val(this.model.get("id"));
            this.IPNSOption.prop("checked",this.model.get("ipns"));
            this.account_details.focus(function(model){ return (model)&&(model.get("stealth"))==account;});
            if(this.model.get("loaded"))
            {
                var details = this.model.get("details");
                this.name.val(details.name);
                if(details.avatar){
                    this.avatarImage.attr("src",details.avatar);
                    this.avatarRemove.show();
                }else{
                    this.avatarImage.attr("src",'img/avatarEmpty.png');
                    this.avatarRemove.hide();
                }
            }
            else
            {
                this.lockPage("loading profile details",true);
                this.model.once("change:loaded", this.reset);
            }
        }else{
            this.bitprofileContext.prop('selectedIndex', 0);
            this.bitprofileId.val("");
            this.name.val("");
            this.IPNSOption.prop("checked",false);
            this.avatarImage.attr("src",'img/avatarEmpty.png');
            this.avatarRemove.hide();
        }

        this.avatar.val("");
        this.bitprofileContext.selectmenu( "refresh" );
        this.IPNSOption.button( "refresh" );
    },

    computeFee: function(){
        var request = this.getFormData();
        request.factor = this.feeFactor.getFeeFactor();
        var result = this.feeModel.estimate(request);
        if(result){
            this.gasAmount = result["gas"];
            this.gasPrice = result["price"];
            this.fee = result["fee"];
        }else{
            this.fee=0;
            this.gasAmount = this.gasPrice = undefined;
        }
        this.feeFactor.update(result);
    },

    setLockMessage:function(msg){
        this.$el.find(".pendingBox h1").html(msg);
    },

    lockPage:function(msg,details){
        this.locks ++;
        this.pending = true;
        if(this.locks == 1){
            this.$el.addClass("pending");
            if(details){
                this.$el.addClass("details");
            }
        }
        this.setLockMessage(msg);
    },

    unlockPage:function(){
        this.locks --;
        if(this.locks <= 0){
            this.locks = 0;
            this.pending = false;
            this.$el.removeClass("pending");
            this.$el.removeClass("details");
        }
    },

    submitDetails:function(){
        if(!$([this.bitprofileId]).validate()){
            this.setIDError("cannot be empty");
            notifyError("please fill all mandatory fields");
            return false;
        }
        if(!this.account_details.selected()){
            notifyError("no stealth address selected");
            return false;
        }
        if(this.validateName()===true){
            this.renderPaymentPage();
        }
    },
    
    submit:function(){
        if(!$([this.password]).validate()){
            notifyError("please fill all mandatory fields");
            return false;
        }
        if(this.account_payment.selected().get("balance")<parseFloat(this.fee)){
            this.accountSelect_payment.error();
            notifyError("not enough funds");
            return false;
        }
        this.resetAddressError();
        this.$form.addClass("waiting");
        this.submitStrategy();
        this.$form.removeClass("waiting");
    },

    risePasswordError:function(){
      this.password.error();  
    },

    getFormData:function(){
        var request = {account:this.account_payment.selected().get("address"), password:this.password.val(), context:this.bitprofileContext.val(), id:(!this.validateName()?null:this.bitprofileId.val().toLowerCase()), stealth:this.account_details.selected().get("stealth"), ipns:this.IPNSOption.prop("checked"), name:this.name.val()};

        var avatar = this.avatar.val();
        if(avatar.length)
        {
            request.avatar = avatar;
        }
        else
        {
            if(this.avatarDeleted)
            {
                request.avatar = null;
            }
        }

        if(this.gasPrice!=undefined && this.gasAmount){
            request.price = this.gasPrice;
            request.gas = this.gasAmount;
        }
        request.feeFactor = this.feeFactor.getFeeFactor();
        return request;
    },
    inProgress:function(){
        return this.pending;
    },
    hasLowFee:function(){
        return this.feeFactor.hasWarning();
    }

});
