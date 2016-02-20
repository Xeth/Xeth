var Progress = Backbone.Model.extend({

    initialize:function(){
        _(this).bindAll("updateScan", "updateSync");
    },

    observe:function(){
        XETH_event.ScanProgress.connect(this, this.updateScan);
        XETH_event.SyncProgress.connect(this, this.updateSync);
    },

    fetch:function(){
        this.set({"sync": progress.getSync(), "scan":progress.getScan()});
    },

    updateScan:function(value){
        this.set({"scan": value});
    },

    updateSync:function(value){
        this.set({"sync": value});
    }

});
