var SendPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("toggleAlias", "updateContact", "resetContact", "scheduleUpdateContact", "updateSendType", "updatePlaceholder", "submit", "checkSubmit", "paste", "computeFee");
        SubPageView.prototype.initialize.call(this,options);
        this.addressbook = options.addressbook;
        this.feeModel = options.fee;
        this.accounts = options.accounts;
        this.template = options.templates.get("send");
        this.placeholders = {bitprofile: "BitProfile ID", address: "Address"};
        this.clipboard = options.clipboard;
        this.addressValidator = options.addressValidator;
        this.$el.html(this.template());
        this.gasPrice = this.$el.find('.section_fee .slider');
        this.gasPrice.slider({value:50, change:this.computeFee});

        this.saveOption = this.$el.find("#saveContact");
        this.saveOption.button({text:false});
        this.sendType = this.$el.find("#sendToType");
        this.sendType.selectmenu().selectmenu( "widget" ).addClass( "type" );
        this.aliasHolder = this.$el.find(".section_alias .input");
        this.alias = this.aliasHolder.find("input");
        this.destination = this.$el.find("#sendToInput");
        this.amount = this.$el.find("#sendAmount");
        this.password = this.$el.find("#sendPassword");
        this.destination.change(this.updateContact);
        this.destination.on("input", this.scheduleUpdateContact);
        this.addressbook.on("remove", this.updateContact);

        this.aliasHolder.hide();
        this.accounts.render();
        this.saveOption.change(this.toggleAlias);
        this.sendType.on("selectmenuchange",this.updateSendType);
        this.updatePlaceholder();
        this.$el.find("#submitSend").click(this.checkSubmit);
        this.$el.find("a.addressbook").click(function(){
            options.router.redirect("addressbook");
        });
        this.$el.find("a.clipboard").click(this.paste);
        this.router = options.router;
        this.$form = this.$el.find(".formpage.send");
        
        this.$el.find('.btn').tooltip({
            position: { my: "center bottom", at: "center top-5" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        
        this.$el.find('.section_fee').tooltip({
            position: { my: "center top", at: "center bottom" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
        this.fee = this.$el.find(".fee .eth");
        this.gas = this.$el.find(".fee .gas");

        this.amount.on("input", this.computeFee);
        this.amount.on("change", this.computeFee);
        this.destination.on("change", this.computeFee);
        this.destination.on("input", this.computeFee);
    },

    render:function(args){
        this.accounts.attach(this.$el.find("#sendFrom"));
        this.accounts.filter(function(model){return model!=undefined&&model.get("address");});
        this.accounts.style("send");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        if(args && args.destination){
            this.setDestination(args.destination);
            this.computeFee();
        }
    },

    setDestination:function(address){
        if(address instanceof Object){
            if(address.bitprofile!=undefined){
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
    },

    setAmount:function(amount){
        this.amount.val(amount);
    },

    updateSendType:function(){
        this.updatePlaceholder();
        if(this.destination.val()) this.updateContact();
    },

    updatePlaceholder:function(){
        this.destination.attr("placeholder", this.placeholders[this.sendType.val()]);
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

    computeFee: function(){
        var factor = this.getFeeFactor();
        var from = this.accounts.selected().get("address");
        var to = this.destination.val();
        var amount = this.amount.val();

        var result = this.feeModel.estimate(from, to, amount, factor);
        if(result){
            this.fee.html(result["fee"].substr(0, 15));
            this.gas.html(result["gas"]);
        }else
        {
            this.fee.html("0");
            this.gas.html("0");
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
        if(account.get("balance")<this.amount.val()){
            this.amount.error();
            notifyError("not enough funds");
            return false;
        }
        var destination = this.destination.val();
        if(destination.length==40||destination.length==42)
        {
            if(this.addressValidator.hasChecksum(destination))
            {
                if(this.addressValidator.validate(destination))
                {
                    this.submit();
                }
                else
                {
                    notifyError("Invalid address checksum");
                    this.destination.error();
                }
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
    },

    getFeeFactor: function(){
        var gas = this.gasPrice.slider("value");
        return parseInt(gas/50*100); //in percents
    },

    submit:function(){
        this.$form.addClass("waiting");
        
        var alias = !this.saveOption.prop("disabled")&&this.saveOption.prop("checked") ? this.alias.val() : "";
        var type = this.sendType.val();
        var request = {amount:this.amount.val(), password:this.password.val(), checksum:false};
        var account = this.accounts.selected();
        
        request[type] = this.destination.val().replace(/^\s+|\s+$/g, '');;
        
        var factor = this.getFeeFactor();
        if(factor!=100){
            request.fee = factor;
        }

        var _this = this;
        setTimeout(function(){
            if(!account.send(request)){
                _this.$form.removeClass("waiting");
                _this.password.error();
                notifyError("invalid password");
                return false;
            }
            
            notifySuccess("sent");

            if(alias.length){
                var contact = {alias:alias};
                contact[type] = request[type];
                _this.addressbook.create(contact);
            }

            _this.resetContact();
            _this.$form.removeClass("waiting");
            _this.password.val("");
            _this.destination.val("");
            _this.amount.val("");

            _this.router.redirect("transactions", {focusFirst:true});
        }, 0);
    }

})
