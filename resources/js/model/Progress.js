var Progress = Backbone.Model.extend({

    initialize:function(){
        _(this).bindAll("updateScan", "updateSync");
    },

    observe:function(){
        XETH_blockchain.ScanProgress.connect(this, this.updateScan);
        XETH_blockchain.SyncProgress.connect(this, this.updateSync);
    },

    fetch:function(){
        this.set({"sync": XETH_blockchain.getSyncProgress(), "scan":XETH_blockchain.getScanProgress()});
    },

    updateScan:function(value){
        this.set({"scan": value});
    },

    updateSync:function(value){
        this.set({"sync": value});
    }

});
