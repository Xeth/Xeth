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
        _(this).bindAll("update");
        this.update();
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
        request.amount = XETH_convert.toWei(""+request.amount);
        var txid = XETH_wallet.send(request);
        if(txid){
            this.update();
        }
        return txid;
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

    initialize:function(){
    
        _(this).bindAll("add");
    },

    add:function(data){
        var account = this.get(data.address||data.stealth);
        if(!account)
        {
            Backbone.Collection.prototype.add.call(this, data);
        }
    },

    observe: function(){
        XETH_event.Account.connect(this, this.add);
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
