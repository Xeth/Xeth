var Progress = Backbone.Model.extend({

    initialize:function(){
        _(this).bindAll("updateScan", "updateSync");
    },

    observe:function(){
        XETH_blockchain.ScanProgress.connect(this, this.updateScan);
        XETH_blockchain.SyncProgress.connect(this, this.updateSync);
        var self = this;
        var callback = function(err, height){
            setTimeout(function(){
                self.updateHeight(callback);
            },1000);
        };
        this.updateHeight(callback);
    },

    fetch:function(){
        this.set({"sync": XETH_blockchain.getSyncProgress(), "scan":XETH_blockchain.getScanProgress(), "height": XETH_blockchain.getChainHeight()});
    },

    updateScan:function(value){
        this.set({"scan": value});
    },

    updateSync:function(value){
        this.set({"sync": value});
    },

    updateHeight:function(callback){
        var future = new FutureObserver(XETH_blockchain.getChainHeightAsync());
        var self = this;
        future.onFinished(function(height){
            self.set("height", height);
            if(callback != undefined) callback(null, height);
        });
    }

});
