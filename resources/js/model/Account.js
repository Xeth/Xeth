
var Account = Backbone.Model.extend({

    idAttribute: "address",

    initialize:function(){

        _(this).bindAll("update");
        this.update();
    },

    update:function(){

        this.set("balance", wallet.getBalance(this.get("address")));
    },


    autoUpdate:function(interval){
        if(typeof interval==undefined||!interval){
            interval = 30000;
        }
        setTimeout(this.update, interval);
    },

    send:function(request){
        request.from = this.get("address");
        var txid = wallet.send(request);
        if(txid){
            this.update();
        }
        return txid;
    }

});
