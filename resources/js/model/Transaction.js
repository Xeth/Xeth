

var TransactionCollection = Backbone.Collection.extend({

    initialize:function(){
        _(this).bindAll("push");
    },

    fetch:function(){
        this.reset(XETH_wallet.listTransactions({}));
    },

    observe:function(){
        XETH_event.Transaction.connect(this, this.add);
    },

    model: function(data){
        data.amount = parseFloat(XETH_convert.fromWei(data.amount));
        data.timestamp = parseInt(data.timestamp) * 1000;
        if(data.amount<0.00000001) data.amount = 0;
        return new Backbone.Model(data);
    }

});
