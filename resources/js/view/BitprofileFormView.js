var BitprofileFormView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("computeFee", "clickGenerate", "clickBrowseAvatar", "clickRemoveAvatar", "submitDetails", "submit", "resetForm", "reset", "lockPage", "renderDetailsPage");
		SubPageView.prototype.initialize.call(this,options);
        this.template = options.templates.get("bitprofile_form");
        this.registrars = options.registrars;
        this.router = options.router;
        this.filesystem = options.filesystem;
        this.pending = false;
        this.avatarDeleted = false;
        
        this.accounts = new AccountSelect({collection:options.accounts, templates:options.templates});
        //this.accounts.filter(function(model){return model!=undefined;}); //hide text
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
        if(this.registrars.length==0) this.bitprofileContext.append("<option>NONE</option>");
        else
        for(var i=0; i<this.registrars.length; i++)
        {
            var registrar = this.registrars.at(i);
            this.bitprofileContext.append("<option>"+registrar.get("uri")+"</option>");
        }
        this.bitprofileContext.selectmenu().selectmenu( "widget" ).addClass( "contextSelect" );
        this.$el.find("#bitporfileCreate_details .btnSubmit").click(this.submitDetails);
        this.$el.find("#bitporfileCreate_payment .btnSubmit").click(this.submit);
        this.$el.find("#bitporfileCreate_details .submitCancel").click(this.resetForm);
        this.$el.find("#bitporfileCreate_payment .submitCancel").click(this.renderDetailsPage);
        this.$el.find(".generate a").click(this.clickGenerate);
        this.avatar.click(this.clickBrowseAvatar);
        this.avatarRemove.click(this.clickRemoveAvatar);
        this.avatarRemove.hide();
        
        this.listenTo(this.accounts, "change", this.resetAddressError);
        
        this.$el.find('.inputBtn').tooltip({
            position: { my: "center bottom", at: "center top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
    },

    exit:function(){
        //this.stopListening(this.accounts, "change", this.resetAddressError);
        this.stopListeningPayments();
    },

    attach:function(dom){
        this.exit();
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
        this.stopListeningPayments();
        
        if(this.accountSelect_details.find(".accountClone").length>0)
        this.accountSelect_details.html('');
        this.account_payment = this.cloneAccount(this.accountSelect_payment);
        
        this.accounts.resize(22);
        this.accounts.compact(true);
        this.accounts.attach(this.accountSelect_details);
        this.accounts.filter(function(model){return model!=undefined&&!model.get("address")&&model.get("stealth");});
        this.accounts.style("mini receive");
        if(this.account_details) this.selectAccount("stealth",this.account_details.get("stealth"));
        
        this.detailsPage.addClass("active");
        this.paymentPage.removeClass("active");
    },

    renderPaymentPage:function(){
        this.accountSelect_payment.html('');
        this.account_details = this.cloneAccount(this.accountSelect_details);
        
        this.accounts.resize(28);
        this.accounts.compact(true);
        this.accounts.attach(this.accountSelect_payment);
        this.accounts.filter(function(model){return model!=undefined&&model.get("address");});
        this.accounts.style("mini send");
        
        if(this.model){
            this.accounts.readonly(true);
            this.selectAccount("address",this.model.get("account"));
        }else{
            if(this.account_payment) this.selectAccount("address",this.account_payment.get("address"));
        }
        this.computeFee();
        this.detailsPage.removeClass("active");
        this.paymentPage.addClass("active");
        this.updatePaymentAccount();
        this.listenTo(this.accounts, "change", this.updatePaymentAccount);
    },

    stopListeningPayments:function(){
        this.stopListening(this.accounts, "change", this.updatePaymentAccount);
        if(this.account_payment) this.stopListening(this.account_payment);
    },

    cloneAccount:function(dom){
        if(dom){
            var currentAccount = '<div class="input accountClone">'+this.accounts.selectedView().$el.html()+'</div>';
            this.accounts.detach();
            dom.html(currentAccount);
        }
        return this.accounts.selected();
    },

    selectAccount:function(type,account){
        this.accounts.focus(function(model){ return (model)&&(model.get(type))==account;});
    },

    updatePaymentAccount:function(){
        if(this.account_payment) this.stopListening(this.account_payment);
        this.account_payment = this.accounts.selected();
        this.updatePaymentAccountBalance();
        this.listenTo(this.account_payment, "change:balance",this.updatePaymentAccountBalance);
    },

    updatePaymentAccountBalance:function(){
        var balance = splitAmount(this.account_payment.get("balance"));
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
        this.password.noerror();
        this.password.val("");
        this.avatarDeleted = false;
        this.fillForm();  
    },

    fillForm:function(){
        if(this.model){
            this.bitprofileContext.val(this.model.get("context"));
            this.bitprofileId.val(this.model.get("id"));
            this.IPNSOption.prop("checked",this.model.get("ipns"));
            this.selectAccount("stealth",this.model.get("payments"));
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

        this.pending = true;
        this.$el.addClass("pending");
        if(details){
            this.$el.addClass("details");
        }else{
            this.account_payment = this.cloneAccount(this.accountSelect_payment);
        }
        this.setLockMessage(msg);
    },

    unlockPage:function(){
        this.pending = false;
        this.$el.removeClass("pending");
        this.$el.removeClass("details");
    },

    submitDetails:function(){
        if(!$([this.bitprofileId]).validate()){
            notifyError("please fill all mandatory fields");
            return false;
        }
        if(!this.accounts.selected()){
            notifyError("no stealth address selected");
            return false;
        }
        this.renderPaymentPage();
    },
    
    submit:function(){
        if(!$([this.password]).validate()){
            notifyError("please fill all mandatory fields");
            return false;
        }
        var account = this.accounts.selected();
        if(account.get("balance")<parseFloat(this.fee)){
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
        var request = {account:this.accounts.selected().get("address"), password:this.password.val(), context:this.bitprofileContext.val(), id:this.bitprofileId.val(), stealth:this.account_details.get("stealth"), ipns:this.IPNSOption.prop("checked"), name:this.name.val()};

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
