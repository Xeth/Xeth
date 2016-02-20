var SendPageView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("toggleAlias", "updateContact", "updatePlaceholder", "submit");
        this.addressbook = options.addressbook;
        this.accounts = options.accounts;
        this.template = _.template($("#send_tpl").html());
        this.placeholders = {bitprofile: "BitProfile ID", address: "Address"};

        this.$el.html(this.template());
        this.gas = this.$el.find('.section_fee .slider');
        this.gas.slider({value:50});

        this.saveOption = this.$el.find("#saveContact");
        this.sendType = this.$el.find("#sendToType select");
        this.aliasHolder = this.$el.find(".section_alias .input");
        this.alias = this.aliasHolder.find("input");
        this.destination = this.$el.find("#sendToInput");
        this.amount = this.$el.find("#sendAmount");
        this.password = this.$el.find("#sendPassword");
        this.destination.change(this.updateContact);

        this.aliasHolder.hide();
        this.accounts.render();
        this.saveOption.change(this.toggleAlias);
        this.sendType.change(this.updatePlaceholder);
        this.updatePlaceholder();
        this.$el.find("#submitSend").click(this.submit);
    },

    render:function(){
        this.accounts.attach(this.$el.find("#sendFrom"));
        this.accounts.filter(function(model){return !model;});
        this.accounts.style("send");
        this.accounts.compact(false);
        this.accounts.resize(); //default size
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
        }
    },

    setAmount:function(amount){
        this.amount.val(amount);
    },

    updatePlaceholder:function(){
        this.destination.attr("placeholder", this.placeholders[this.sendType.val()]);
    },

    updateContact: function(){
        var type = this.sendType.val();
        var address = this.destination.val();
        var contact = this.addressbook.find(function(model) { return model.get(type) === address; });
        if(contact){
            this.saveOption.attr("checked", 1).attr("disabled",1);
            this.alias.val(contact.get("alias")).attr("disabled",1);
            this.aliasHolder.show();
        }else{
            if(this.saveOption.is(":disabled")){
                this.alias.removeAttr("disabled").val("");
                this.saveOption.removeAttr("checked").removeAttr("disabled");
                this.aliasHolder.hide();
            }
        }
    },

    toggleAlias:function(){
        this.aliasHolder.toggle();
    },

    submit:function(){
        var toValidate = [this.amount, this.destination, this.password];

        if(!this.saveOption.is(":disabled")&&this.saveOption.is(":checked")){
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

        var type = this.sendType.val();
        var request = {amount:this.amount.val(), password:this.password.val()};
        var account = this.accounts.selected();

        if(account.get("balance")<request.amount){
            this.amount.error();
            notifyError("not enough funds");
            return false;
        }

        request[type] = this.destination.val();
        var gas = this.gas.slider("value");
        if(gas!=50) request.gas = gas/50; //in percents

        if(!account.send(request)){
            notifyError("invalid password");
            return false;
        }

        notifySuccess("sent");

        if(alias.length){
            var contact = {alias:alias};
            contact[type] = request[type];
            this.addressbook.create(contact);
        }
        return true;

    }

})
