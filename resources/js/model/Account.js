
var Account = Backbone.Model.extend({

    idAttribute: "address",

    initialize:function(){
        _(this).bindAll("update");
        this.update();
    },

    update:function(){
        this.set("balance", XETH_wallet.getBalance(this.get("address")));
    },

    autoUpdate:function(interval){
        if(typeof interval==undefined||!interval){
            interval = 30000;
        }
        setTimeout(this.update, interval);
    },

    send:function(request){
        request.from = this.get("address");
        var txid = XETH_wallet.send(request);
        if(txid){
            this.update();
        }
        return txid;
    },
    
    backup:function(path){
        return XETH_wallet.exportKey({address:this.get("address")||this.get("stealth"), path:path});
    },

    changePassword:function(previous, password){
        return XETH_wallet.changePassword({previous: previous, password:password});
    }

});


var StealthAccount = Backbone.Model.extend({
    idAttribute: "address",
    initialize:function(){
        this.set("balance",0);
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

    observe: function(){
        XETH_event.Account.connect(this, this.add);
    },

    fetch:function(){
        var accounts = XETH_wallet.getAccounts();
        this.reset(accounts);
    },

    generate:function(request){
        return XETH_wallet.generateAccount(request);
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
