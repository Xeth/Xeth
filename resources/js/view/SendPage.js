var SendPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("open", "toggleAlias", "updateContact", "resetContact", "scheduleUpdateContact", "updateSendType", "updatePlaceholder", "submit", "checkSubmit", "paste", "computeFee", "checkAmount", "inputAmount", "changeAccount", "copyAddressHintToClipboard", "resolveProfile", "resolveProfileLater", "clickAddressbook");
        SubPageView.prototype.initialize.call(this,options);
        this.addressbook = options.addressbook;
        this.resolver = options.resolver;
        this.feeModel = options.fee;
        this.accounts = options.accounts;
        this.template = options.templates.get("send");
        this.placeholders = {bitprofile: "BitProfile ID", address: "Address"};
        this.placeholderErrors = {bitprofile: "selected profile is not accepting payments", address: "invalid"};
        this.clipboard = options.clipboard;
        this.addressValidator = options.addressValidator;
        this.router = options.router;
        
        this.accounts = new AccountSelect({collection:options.accounts, templates:options.templates});
        this.accounts.filter(function(model){return model!=undefined&&model.get("address");});
    },

    render:function(){
        this.$el.html(this.template());
        
        this.feeFactor = new FeeSlider({el:this.$el.find(".section_fee")});
        this.feeFactor.on("change", this.computeFee);
        this.feeFactor.on("autoupdate", this.checkAmount);
        
        this.saveOption = this.$el.find("#saveContact");
        this.saveOption.button({text:false});
        this.sendType = this.$el.find("#sendToType");
        this.sendType.selectmenu().selectmenu( "widget" ).addClass( "type" );
        this.aliasHolder = this.$el.find(".section_alias .input");
        this.alias = this.aliasHolder.find("input");
        this.destination = this.$el.find("#sendToInput");
        this.amount = this.$el.find("#sendAmount");
        this.password = this.$el.find("#sendPassword");
        this.addressHint = this.$el.find("#sendToHint");
        this.destination.change(this.updateContact);
        this.destination.on("input", this.scheduleUpdateContact);
        this.addressbook.on("remove", this.updateContact);
        this.destTitle = this.$el.find(".section_to h1");

        this.aliasHolder.hide();
        this.saveOption.change(this.toggleAlias);
        this.sendType.on("selectmenuchange",this.updateSendType);
        this.updatePlaceholder();
        this.$el.find("#submitSend").click(this.checkSubmit);
        this.$el.find("a.addressbook").click(this.clickAddressbook);
        this.$el.find("a.clipboard").click(this.paste);
        this.$form = this.$el.find(".formpage.send");
        
        this.$el.find('.btn').tooltip({
            position: { my: "center bottom", at: "center top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        
        this.addressHint.click(this.copyAddressHintToClipboard);
        this.$el.find(".hint").tooltip({
            position: { my: "center bottom-5", at: "center top" },
            track: true,
            show: { duration: 200 },
            hide: { duration: 200 }
        });

        this.amount.on("input", this.inputAmount);
        this.amount.on("change", this.inputAmount);
        this.destination.on("change", this.computeFee);
        
        this.accounts.style("send");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        this.accounts.attach(this.$el.find("#sendFrom"));
        this.accounts.render();
        
        this.listenTo(this.accounts, "change", this.changeAccount);
    },

    open:function(args){
        if(args && args.destination){
            this.setDestination(args.destination);
            this.computeFee();
        }
    },
    
    clickAddressbook:function(){
        this.router.redirect("addressbook");
    },
    
    setDestination:function(address){
        if(address instanceof Object){
            if(address.bitprofile){
                this.sendType.val("bitprofile");
                this.destination.val(address.bitprofile);
            }else{
                this.sendType.val("address");
                this.destination.val(address.address);
            }
        }else{
            this.destination.val(address);
            this.sendType.val("address");
        }
        this.sendType.selectmenu( "refresh" );
        this.updatePlaceholder();
        this.updateContact();
        this.updateSendType();
    },

    getDestination:function(){
        return this.addressHint.val()||this.destination.val().replace(/^\s+|\s+$/g, '');
    },

    setAmount:function(amount){
        this.amount.val(amount);
    },

    updateSendType:function(){
        this.destination.noerror();
        this.updatePlaceholder();
        if(this.destination.val()) this.updateContact();
        if(this.sendType.val()=="bitprofile"){
            this.resolveProfile();
            this.destination.on("input", this.resolveProfileLater);
            this.destination.on("change", this.resolveProfile)
        }else{
            this.setAddressHint("");
            this.destination.off("input", this.resolveProfileLater);
            this.destination.off("change", this.resolveProfile);
        }
    },

    resolveProfileLater:function(){
        this.clearResolverTimer();
        this.resolverTimer = setTimeout(this.resolveProfile, 1000);
    },

    clearResolverTimer:function(){
        if(this.resolverTimer) clearTimeout(this.resolverTimer);
        this.resolverTimer=undefined;
    },

    resolveProfile:function(){
        this.clearResolverTimer();
        var uri = this.destination.val();
        if(uri){
            var address = this.resolver.getPaymentAddress(uri);
            if(address){
                this.setAddressHint(address);
                this.destination.noerror();
            }
            else{
                this.riseProfileError();
            }
        }
    },

    riseProfileError:function(){
        this.setAddressHint("");
        this.destination.error();
    },

    updatePlaceholder:function(){
        this.destination.attr("placeholder", this.placeholders[this.sendType.val()]);
        this.destTitle.attr("error", this.placeholderErrors[this.sendType.val()]);
    },

    updateContact: function(){
        this.timer = undefined;
        var type = this.sendType.val();
        var address = this.destination.val();
        var contact = this.addressbook.find(function(model) { return model.get(type) === address; });
        if(contact){
            this.destination.noerror();
            this.saveOption.prop("checked",true).prop("disabled",true);
            this.alias.val(contact.get("alias")).prop("disabled",true).noerror();
            this.aliasHolder.show();
            this.saveOption.button( "refresh" );
        }else{
            if(this.saveOption.prop("disabled")){
                this.resetContact();
            }
        }
    },
    
    changeAccount:function(){
        this.useFullAmount = false;
        this.computeFee();
    },

    computeFee: function(){
        var to = this.getDestination();
        if(to){
            var amount = this.amount.val();
            var factor = this.feeFactor.getFeeFactor();
            var account = this.accounts.selected();
            var from = account? account.get("address") : "";
            var result = this.feeModel.estimate(from, to, amount, factor);
            if(result){
                this.gasAmount = result["gas"];
                this.gasPrice = result["price"];
                this.fee = result["fee"];
            }else{
                this.fee=0;
                this.gasAmount = this.gasPrice = undefined;
            }
            this.feeFactor.update(result);
        }else{
            this.fee = 0;
        }
        this.checkAmount(this.fee);
    },
    
    inputAmount:function(){
//        this.checkAmount(this.fee,true);
        this.computeFee();
    },
    
    checkAmount:function(fee){
        if(!fee) fee=this.fee;
        var account = this.accounts.selected();
        var balance = account ? account.get("balance"): 0;
        var amount = this.amount.val();
        var balanceAvailable = balance-fee;
        
        if(balanceAvailable<0) balanceAvailable=0;
        if(amount>=balanceAvailable){//||(!input&&amount<=balanceAvailable&&this.useFullAmount==true)){
            if(balanceAvailable>0){
                amount=parseFloat(balanceAvailable);
            }else{
                amount="";
            }
            this.amount.val(amount);
            this.useFullAmount = true;
        }else{
            this.useFullAmount = false;
        }
    },
    
    resetContact: function(){
        this.alias.val("").prop("disabled",false);
        this.saveOption.prop("checked",false).prop("disabled",false);
        this.aliasHolder.hide();
        this.saveOption.button( "refresh" );
    },

    scheduleUpdateContact:function(){
        if(this.timer==undefined){
            this.timer = setTimeout(this.updateContact, 1000);
        }
    },

    toggleAlias:function(){
        this.aliasHolder.toggle();
    },

    paste:function(){
        this.destination.val(this.clipboard.getText());
        this.updateContact();
        this.updateSendType();
    },
    
    setAddressHint:function(msg){
        this.addressHint.html(shortify(msg,50));
        this.addressHint.val(msg);
    },
    
    copyAddressHintToClipboard:function(){
        if(this.clipboard.setText(this.addressHint.val()))
        {
            notifySuccess("address copied to clipboard");
        }
        else
        {
            notifyError("failed to copy address");
        }
    },
    
    checkSubmit:function(){
        var toValidate = [this.amount, this.destination, this.password];
        var saveAlias = !this.saveOption.prop("disabled")&&this.saveOption.prop("checked");
        if(saveAlias) toValidate.push(this.alias);

        if(!$(toValidate).validate()){
            notifyError("please fill all mandatory fields correctly");
            return false;
        }

        if(saveAlias)
        {
            var alias = this.alias.val();
            if(alias.length && this.addressbook.get(alias)){
                notifyError("alias already registered");
                this.alias.error();
                return false;
            }
            this.alias.noerror();
        }
        
        var account = this.accounts.selected();
        if(!account || (account.get("balance")<(parseFloat(this.amount.val()) + parseFloat(this.fee)))){
            this.amount.error();
            notifyError("not enough funds");
            return false;
        }
        if(this.sendType.val()=="bitprofile"){
            if(!this.addressHint.val()){
                this.riseProfileError();
            }
            else
            {
                this.submit();
            }
        }
        else
        {
            var destination = this.destination.val();
            if(destination.length==40||destination.length==42)
            {
                if(this.addressValidator.hasChecksum(destination))
                {
                    this.submit(true);
                } 
                else 
                {
                    notie.confirm('<span class="title warning">WARNING!</span>'+
                      'Destination address has no checksum!<br>'+
                      'You can send a small test amount first or continue with the transaction<br>'+
                      '<span class="question">Proceed with this transaction?<span>', 
                      'Yes, Send it anyway', 
                      'No, I will try small test amount first', 
                      this.submit);
                }
            }
            else
            {
                this.submit();
            }
        }
    },
    
    submit:function(checksum){
        var alias = !this.saveOption.prop("disabled")&&this.saveOption.prop("checked") ? this.alias.val() : "";
        var type = this.sendType.val();
        var request = {amount:((this.useFullAmount)?"all":this.amount.val()), password:this.password.val(), checksum:false};
        var account = this.accounts.selected();
        var destination = this.getDestination();
        request.address = destination;
        if(type=="bitprofile"){
            request.logs = {bitprofile: this.destination.val()};
        }
        if(checksum){
            if(!this.addressValidator.validate(destination))
            {
                notifyError("Invalid address checksum");
                this.destination.error();
                return false;
            }
        }else{
            if(!this.addressValidator.validateNoChecksum(destination)){
                notifyError("Invalid address");
                this.destination.error();
                return false;
            }
        }

        this.$form.addClass("waiting");

        if(this.gasPrice!=undefined && this.gasAmount){
            request.price = this.gasPrice;
            request.gas = this.gasAmount;
        }

        var _this = this;
        var sendRequest = function(){
            _this.$form.addClass("waiting");
            if(!account.send(request)){
                _this.$form.removeClass("waiting");
                _this.password.error();
                return false;
            }
            
            notifySuccess("sent");

            if(alias.length){
                var contact = {alias:alias};
                contact[type] = _this.destination.val();
                _this.addressbook.create(contact);
            }

            _this.resetContact();
            _this.$form.removeClass("waiting");
            _this.password.val("");
            _this.destination.val("");
            _this.amount.val("");
            _this.setAddressHint("");

            _this.router.redirect("transactions", {focusFirst:true});
        };
        if(this.feeFactor.hasWarning()){
            notie.confirm('<span class="title warning">WARNING!</span>'+
              'Fee is too low!<br>'+
              'Transaction may not be mined or even propagated<br>'+
              '<span class="question">Are you sure you want to send it?<span>', 
              'Yes, Send it anyway', 
              'No, I will change fee', 
             sendRequest);
            
            this.$form.removeClass("waiting");
        }
        else{
            setTimeout(sendRequest, 0);
        }
    }

})
