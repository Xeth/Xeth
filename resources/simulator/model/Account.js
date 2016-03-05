
var AccountSimulator = Account.extend({

    idAttribute: "address",


    update:function(){},
    autoUpdate:function(interval){},

    send:function(request){
        return true;
    }
});


var StealthAccountSimulator = StealthAccount.extend({

    idAttribute: "stealth",

    initialize:function(){
        this.set("balance",0);
    },

    update:function(){},
    autoUpdate:function(){},
    send:function(){
        return false;
    }
});


var AccountCollectionSimulator = AccountCollection.extend({

    observe: function(){},
    fetch:function(){},

    generate:function(request){
		console.log(request);
		var account = {balance:0};
		var address = Math.random();
		account[(request.type=="stealth")? "stealth":"address"] = address;
		this.add(account);
		return address;
    },

    importKey:function(file, password){
        return false;
    },

    modelId: function(attrs){
        return attrs.address;
    },

    model: function(attrs, options) {
        var account;
        if(attrs.address==undefined){
            account = new StealthAccountSimulator(attrs, options);
        }
        else{
            account = new AccountSimulator(attrs, options);
        }
        account.autoUpdate();
        return account;
    },

    sync:function(){}

});
