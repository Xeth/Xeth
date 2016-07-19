var Progress = Backbone.Model.extend({

    initialize:function(){
        _(this).bindAll("updateScan", "updateSync");
    },

    observe:function(){
        XETH_progress.Scan.connect(this, this.updateScan);
        XETH_progress.Sync.connect(this, this.updateSync);
    },

    fetch:function(){
        this.set({"sync": XETH_progress.getSync(), "scan":XETH_progress.getScan()});
    },

    updateScan:function(value){
        this.set({"scan": value});
    },

    updateSync:function(value){
        this.set({"sync": value});
    }

});
