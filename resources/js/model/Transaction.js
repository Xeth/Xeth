
var TransactionCollection = Backbone.Collection.extend({

    initialize:function(options){
        _(this).bindAll("add");
        this.limit = (options&&options.limit)?options.limit:100;
    },

    fetch:function(){
        this.reset(XETH_wallet.listTransactions({limit:this.limit}));
    },

    observe:function(){
        XETH_event.Transaction.connect(this, this.add);
    },

    add:function(model){
        Backbone.Collection.prototype.add.call(this, model);
        while(this.length>this.limit)
        {
            this.pop();
        }
    },

    comparator:function(model){
        return -model.get("timestamp");
    },

    model: function(data){
        data.amount = parseFloat(XETH_convert.fromWei(data.amount));
        data.timestamp = parseInt(data.timestamp) * 1000;
        if(data.amount<0.00000001) data.amount = 0;
        return new Backbone.Model(data);
    }

});
