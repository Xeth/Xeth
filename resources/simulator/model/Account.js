
var AccountSimulator = Account.extend({

    idAttribute: "address",


    update:function(){},
    autoUpdate:function(interval){},

    send:function(request){
        return true;
    },
    
    changePassword:function(previous, password){
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

    initialize: function(){},
    observe: function(){},
    fetch:function(){},

    generate:function(request){
		console.log(request);
		var account = {balance:0};
		var address = "0x0NeW1"+Math.random();
		account[(request.type=="stealth")? "stealth":"address"] = address;
		this.add(account);
		return address;
    },

    importKey:function(file, password){
        this.add({balance:0,address:"0ximpOrt"+Math.random()});
        return true;
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
