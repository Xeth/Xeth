var AppInfo = Backbone.Model.extend({

    initialize:function(options){
        _(this).bindAll("updateLatest", "update");
        this.events = options.events
    },

    observe:function(){
        this.observing = true;
        this.events.onData("update", this.updateLatest);
    },

    update:function(data){
        this.set("version", data.version);
        this.set("client", data.client);
        if(!this.observing)
        {
            this.updateLatest(data.latest);
        }
    },

    updateLatest:function(data){
        var newerClientVersion = data.client;
        var newerVersion = data.version;

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
