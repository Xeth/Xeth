var AccountBase = Backbone.Model.extend({

    getAddress:function(){
        return this.get("address")||this.get("stealth");
    },

    backup:function(path){
        return XETH_wallet.exportKey({address:this.getAddress(), path:path});
    },

    changePassword:function(previous, password){
        return XETH_wallet.changePassword({password: previous, newPassword:password, address:this.getAddress()});
    }
});

var Account = AccountBase.extend({

    idAttribute: "address",

    initialize:function(){
        _(this).bindAll("update", "removeIfEmpty", "destroy");
        this.update();
        if(this.get("stealth"))
        {
            this.on("change:balance", this.removeIfEmpty);
        }
    },

    removeIfEmpty: function(){
        if((this.get("balance")==0)&&(this.get("unconfirmed")==0))
        {
            this.trigger("removing");
            setTimeout(this.destroy, 30000);
        }
    },

    update:function(){
        var address = this.get("address");
        this.set("balance", XETH_convert.fromWei(XETH_wallet.getBalance(address)));
        this.set("unconfirmed", XETH_convert.fromWei(XETH_wallet.getPendingBalance(address)));
    },

    autoUpdate:function(interval){
        if(typeof interval==undefined||!interval){
            interval = 10000;
        }
        setInterval(this.update, interval);
    },

    send:function(request){
        request.from = this.get("address");
        if(!isNaN(request.amount))
        {
            request.amount = XETH_convert.toWei(""+request.amount);
        }
        var txid = XETH_wallet.send(request);
        if(txid){
            this.update();
        }
        return txid;
    },

    destroy: function(){
        if(this.interval) clearInterval(this.interval);
        this.trigger("destroy", this);
    }

});


var StealthAccount = AccountBase.extend({

    idAttribute: "stealth",

    initialize:function(){
        this.set("balance",0);
        this.set("unconfirmed", 0);
    },

    update:function(){},
    autoUpdate:function(){},
    send:function(){
        return false;
    }
});


var AccountCollection = Backbone.Collection.extend({

    initialize:function(models, options){
        _(this).bindAll("add", "parseNew");
        this.profiles = options.profiles;
    },

    add:function(data){
        var account = this.get(data.address||data.stealth);
        if(!account)
        {
            Backbone.Collection.prototype.add.call(this, data);
        }
    },

    cleanEmptyStealth:function(){
        var self = this;
        var filtered = [];
        this.each(function(model){
            if(model.get("stealth")&&model.get("address"))
            {
                if(model.get("balance")==0 && model.get("unconfirmed")==0)
                {
                    //check if is not used in bitprofile
                    if(!self.profiles.find({account:model.get("address")}))
                    {
                        filtered.push(model);
                    }
                }
            }
        });
        for(var i in filtered)
        {
            this.remove(filtered[i]);
        }
        this.cleanEnabled = true;
    },

    observe: function(){
        XETH_event.Account.connect(this, this.parseNew);
    },

    parseNew: function(data){
        if(this.cleanEnabled && data.stealth && data.address)
        {
            var model = new Account(data);
            if(model.get("balance") != 0 || model.get("unconfirmed") != 0 || this.profiles.find({account:model.get("address")})) this.add(model);
        }
        else
        {
            this.add(data);
        }
    },

    fetch:function(){
        var accounts = XETH_wallet.getAccounts();
        this.reset(accounts);
    },

    generate:function(request){
        return XETH_wallet.generateKey(request);
    },

    importKey:function(file, password){
        var request = {file:file, password:password};
        return XETH_wallet.importKey(request);
    },

    modelId: function(attrs){
        return attrs.address;
    },

    model: function(attrs, options) {
        var account;
        if(attrs.address==undefined){
            account = new StealthAccount(attrs, options);
        }
        else{
            account = new Account(attrs, options);
        }
        account.autoUpdate();
        return account;
    },

    sync:function(){}

});
