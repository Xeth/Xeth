var AppInfo = Backbone.Model.extend({

    initialize:function(options){
        _(this).bindAll("updateLatest", "update");
        this.events = options.events
    },

    observe:function(){
        this.observing = true;
        this.events.onData("update", this.updateLatest);
    },

    update:function(){
        this.set("version", XETH_system.getVersion());
        this.set("client", XETH_system.getClientVersion());
        XETH_system.updateLatestReleaseInfo();
        if(!this.observing)
        {
            this.updateLatest();
        }
    },

    updateLatest:function(){
        var newerClientVersion = XETH_system.getNewerClientVersion();
        var newerVersion = XETH_system.getNewerXethVersion();

        if(newerClientVersion){
            this.set({"clientUpdate": true, "latestClient": newerClientVersion});
        }
        else{
            this.set({"latestClient": this.get("client"), "clientUpdate": false});
        }

        if(newerVersion){
            this.set({"xethUpdate": true, "latest": newerVersion});
        }else{
            this.set({"xethUpdate": false, "latest": this.get("version")});
        }
    }

});
