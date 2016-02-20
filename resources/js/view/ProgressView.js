var ProgressView = Backbone.View.extend({

    initialize:function(options){
        _(this).bindAll("updateSync", "updateScan", "watchSync");
        this.$bar = this.$el.find('.status .loader .value');
        this.$status = this.$el.find(".status");
        this.$text = this.$el.find(".status .message");
        this.$icon = this.$el.find(".icons .updated");
    },

    render:function(){
        this.startSync();
    },

    startSync:function(){
        this.setMessage("Synchronizing with network");
        this.listenTo(this.model, "change:sync", this.updateSync);
        this.updateSync();
    },

    updateSync:function(){
        var progress = this.model.get("sync");
        this.updateProgressBar(progress);
        if(progress>=99.99){
            this.setMessage("Scanning blockchain");
            this.stopListening();
            this.listenTo(this.model, "change:scan", this.updateScan);
            this.updateScan();
        }
    },

    updateScan:function(){
        var progress = this.model.get("scan");
        this.updateProgressBar(progress);
        if(progress>=99.99){
            this.stopListening();
            this.listenTo(this.model, "change:sync", this.watchSync);
            this.$icon.addClass("ok");
        }
    },

    updateProgressBar:function(val){
        this.$bar.css('width', val+'%');
        this.$status.attr('loader', val);
    },

    watchSync:function(){
        var progress = this.model.get("sync");
        if(progress<97){
            this.$icon.removeClass("ok");
            this.stopListening();
            this.startSync();
        }
    },

    setMessage:function(txt){
        this.$text.html(txt);
    }

});
