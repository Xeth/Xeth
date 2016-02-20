var Transaction = Backbone.Model.extend({
    initialize: function(){
        //resolve alias
    }
});

var TransactionCollection = Backbone.Collection.extend({

    model: Transaction, 

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
