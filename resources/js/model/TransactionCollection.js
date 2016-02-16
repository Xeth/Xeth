var TransactionCollection = Backbone.Collection.extend({

    initialize:function(){
        _(this).bindAll("push");
    },

    fetch:function(){
        this.reset(wallet.listTransactions({}));
    },

    observe:function(){
        event.Transaction.connect(this, this.push);
    }

});
