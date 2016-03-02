
var TransactionCollectionSimulator = TransactionCollection.extend({

    fetch:function(){},
    observe:function(){},
    model: function(data){
        data.timestamp = parseInt(data.timestamp) * 1000;
        if(data.amount<0.00000001) data.amount = 0;
        return new Backbone.Model(data);
    }

});
