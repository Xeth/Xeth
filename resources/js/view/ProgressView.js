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
        this.$icon.removeClass("ok");
        this.setMessage("Synchronizing with network");
        this.listenTo(this.model, "change:sync", this.updateSync);
        this.updateSync();
    },

    startScan:function(){
        this.$icon.removeClass("ok");
        this.setMessage("Scanning blockchain");
        this.stopListening();
        this.listenTo(this.model, "change:scan", this.updateScan);
        this.updateScan();
    },

    updateSync:function(){
        var progress = this.model.get("sync");
        this.updateProgressBar(progress);
        if(progress>=99.99){
            this.startScan();
        }
    },

    updateScan:function(){
        var progress = this.model.get("scan");

        if(progress>=99.99){
            this.stopListening();
            this.listenTo(this.model, "change:sync", this.watchSync);
            this.$icon.addClass("ok");
            this.updateProgressBar(100);
        }else{
            this.updateProgressBar(progress);
        }
    },

    updateProgressBar:function(val){
        this.$bar.css('width', val+'%');
        this.$status.attr('loader', val);
    },

    watchSync:function(){
        var progress = this.model.get("sync");
        if(progress<99){
            this.stopListening();
            this.startSync();
        }else{
            progress = this.model.get("scan");
            if(progress<99)
            {
                this.stopListening();
                this.startSync();
            }
        }
    },


    setMessage:function(txt){
        this.$text.html(txt);
    }

});
