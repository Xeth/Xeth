var SendPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("toggleAlias", "updateContact", "resetContact", "scheduleUpdateContact", "updateSendType", "updatePlaceholder", "submit", "paste");
		SubPageView.prototype.initialize.call(this,options);
        this.addressbook = options.addressbook;
        this.accounts = options.accounts;
        this.template = options.templates.get("send");
        this.placeholders = {bitprofile: "BitProfile ID", address: "Address"};
        this.clipboard = options.clipboard;
        this.$el.html(this.template());
        this.gas = this.$el.find('.section_fee .slider');
        this.gas.slider({value:50});

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
        this.$el.find("#submitSend").click(this.submit);
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
    },

    render:function(args){
        this.accounts.attach(this.$el.find("#sendFrom"));
        this.accounts.filter(function(model){return model!=undefined&&model.get("address");});
        this.accounts.style("send");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
        if(args && args.destination){
            this.setDestination(args.destination);
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

    submit:function(){
        var toValidate = [this.amount, this.destination, this.password];

        if(!this.saveOption.prop("disabled")&&this.saveOption.prop("checked")){
            toValidate.push(this.alias);
        }

        if(!$(toValidate).validate()){
            notifyError("please fill all mandatory fields correctly");
            return false;
        }

        var alias = this.alias.val();
        if(alias.length && this.addressbook.get(alias)){
            notifyError("alias already registered");
            this.alias.error();
            return false;
        }
		this.alias.noerror();
		
        var type = this.sendType.val();
        var request = {amount:this.amount.val(), password:this.password.val()};
        var account = this.accounts.selected();

        if(account.get("balance")<request.amount){
            this.amount.error();
            notifyError("not enough funds");
            return false;
        }

        request[type] = this.destination.val().replace(/^\s+|\s+$/g, '');;
        var gas = this.gas.slider("value");
        if(gas!=50) request.gas = gas/50; //in percents

        this.$form.addClass("waiting");
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
