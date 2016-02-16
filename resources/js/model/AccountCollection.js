var AccountCollection = Backbone.Collection.extend({

    initialize:function(){
    
        _(this).bindAll("add");
    },

    observe: function(){
        event.Account.connect(this, this.add);
    },

    fetch:function(){
        var accounts = wallet.getAccounts();
        this.reset(accounts);
    },


    modelId: function(attrs){
        return attrs.address;
    },

    model: function(attrs, options) {
        var account;
        if(typeof attrs.stealth!= "undefined" && attrs.stealth){
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
