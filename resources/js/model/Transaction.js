

var TransactionCollection = Backbone.Collection.extend({

    initialize:function(){
        _(this).bindAll("push");
    },

    fetch:function(){
        this.reset(XETH_wallet.listTransactions({}));
    },

    observe:function(){
        XETH_event.Transaction.connect(this, this.push);
    }

});
