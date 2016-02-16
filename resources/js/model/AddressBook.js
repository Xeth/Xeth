var AddressBook = Backbone.Collection.extend({

    model: Contact,

    fetch:function(){
        var contacts = addressbook.listContacts();
        if(contacts.length){
            this.reset(contacts);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    rename:function(oldName, newName){

        if(addressbook.renameContact({oldName:oldName, newName:newName})){
            var contact = this.get(oldName);
            this.remove(contact, {silent:true});
            contact.set("alias", newName);
            this.add(contact, {silent: true});
            this.emit("update", contact);
            return true;
        }
        return false;
    },

    observe:function(){
        event.Contact.connect(this, Backbone.Collection.prototype.add);
    },


});
